#include "stdafx.h"
#include "StageCollision.h"

StageCollision::StageCollision() {}

void StageCollision::SetStageCollision(const int collisionModelHandle)
{
    modelHandle = collisionModelHandle;
}

/// <summary>
/// 当たり判定をして、補正した移動先のポジションを返す
/// </summary>
VECTOR StageCollision::CheckCollision(IGameObject& object, const VECTOR& nextPos)
{
    VECTOR oldPos = object.GetPosition();       // 移動前の座標
    VECTOR newPos = nextPos;

    // プレイヤーの周囲にあるステージポリゴンを取得する
    // ( 検出する範囲は移動距離も考慮する )
    auto hitDim = MV1CollCheck_Sphere(modelHandle, -1, oldPos, DefaultSize + VSize(newPos));

    // 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
    AnalyzeWallAndFloor(hitDim, oldPos);

    // 壁ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    newPos = CheckHitWithWall(object, newPos);

    // 床ポリゴンとの当たりをチェックし、移動ベクトルを補正する
    newPos = CheckHitWithFloor(object, newPos);

    // 検出したプレイヤーの周囲のポリゴン情報を開放する
    MV1CollResultPolyDimTerminate(hitDim);

    return newPos;
}

/// <summary>
/// 検出されたポリゴンが壁ポリゴン( ＸＺ平面に垂直なポリゴン )か床ポリゴン( ＸＺ平面に垂直ではないポリゴン )かを判断し、保存する
/// </summary>
void StageCollision::AnalyzeWallAndFloor(MV1_COLL_RESULT_POLY_DIM hitDim, const VECTOR& checkPosition)
{
    // 壁ポリゴンと床ポリゴンの数を初期化する
    wallNum = 0;
    floorNum = 0;

    // 検出されたポリゴンの数だけ繰り返し
    for (int i = 0; i < hitDim.HitNum; i++)
    {
        const auto& poly = hitDim.Dim[i];
        // ＸＺ平面に垂直かどうかはポリゴンの法線のＹ成分が０に限りなく近いかどうかで判断する
        if (poly.Normal.y < 0.000001f && poly.Normal.y > -0.000001f)
        {
            if ((poly.Position[0].y > checkPosition.y + 1.0f ||
                poly.Position[1].y > checkPosition.y + 1.0f ||
                poly.Position[2].y > checkPosition.y + 1.0f) && wallNum < MaxHitColl)
            {
                wall[wallNum++] = &hitDim.Dim[i];
            }
        }
        else
        {
            if (floorNum < MaxHitColl)
            {
                floor[floorNum++] = &hitDim.Dim[i];
            }
        }
    }
}

/// <summary>
/// 壁ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
/// </summary>
VECTOR StageCollision::CheckHitWithWall(IGameObject& object, const VECTOR& checkPosition)
{
    VECTOR fixedPos = checkPosition;

    float HitRadius = object.GetHitRadius();
    float HitHeight = object.GetHitHeight();

    // 壁の数が無かったら早期リターン
    if (wallNum == 0)
        return fixedPos;

    // 壁からの押し出し処理を試みる最大数だけ繰り返し
    for (int k = 0; k < HitTryNum; k++)
    {
        // 当たる可能性のある壁ポリゴンを全て見る
        bool isHitWall = false;
        for (int i = 0; i < wallNum; i++)
        {
            // i番目の壁ポリゴンのアドレスを壁ポリゴンポインタ配列から取得
            auto poly = wall[i];

            // プレイヤーと当たっているなら
            if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)), HitRadius,
                poly->Position[0], poly->Position[1], poly->Position[2]))
            {
                // 規定距離分プレイヤーを壁の法線方向に移動させる
                // 移動後の位置を更新（移動後の場所を補正）
                fixedPos = VAdd(fixedPos, VScale(poly->Normal, HitSlideLength));

                // 移動した壁ポリゴンと接触しているかどうかを判定
                for (int j = 0; j < wallNum; j++)
                {
                    // 当たっていたらループを抜ける
                    auto checkPoly = wall[j];
                    if (HitCheck_Capsule_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)), HitRadius,
                        checkPoly->Position[0], checkPoly->Position[1], checkPoly->Position[2]))
                    {
                        isHitWall = true;
                        break;
                    }
                }

                // 全てのポリゴンと当たっていなかったらここでループ終了
                if (!isHitWall) break;
            }
        }

        // 全部のポリゴンで押し出しを試みる前に
        // 全ての壁ポリゴンと接触しなくなったらループから抜ける
        if (!isHitWall)
            break;
    }

    return fixedPos;
}

/// <summary>
/// 床ポリゴンとの当たりをチェックし、補正すべき移動ベクトルを返す
/// </summary>
VECTOR StageCollision::CheckHitWithFloor(IGameObject& object, const VECTOR& checkPosition)
{
    VECTOR fixedPos = checkPosition;
    float HitHeight = object.GetHitHeight();

    // 床の数が無かったら早期リターン
    if (floorNum == 0)
        return fixedPos;

    float jumpPower = object.GetJumpPower();

    // ジャンプ中且つ上昇中の場合は処理を分岐
    if (object.GetIsJumping() && jumpPower > 0.0f) // Jumping upward
    {
        // 天井に頭をぶつける処理を行う
        // 一番低い天井にぶつける為の判定用変数を初期化
        bool isHitRoof = false;
        float minY = 0.0f;

        // 床ポリゴンの数だけ繰り返し
        for (int i = 0; i < floorNum; i++)
        {
            auto poly = floor[i];   // i番目の床ポリゴンのアドレス

            // 足先から頭の高さまでの間でポリゴンと接触しているかどうかを判定
            // 線分とポリゴンとの当たり判定の結果を代入する構造体
            HITRESULT_LINE lineResult = HitCheck_Line_Triangle(fixedPos, VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)),
                poly->Position[0], poly->Position[1], poly->Position[2]);

            // 接触していなかったら何もしない
            if (lineResult.HitFlag)
            {
                // 既にポリゴンに当たっていて、且つ今まで検出した天井ポリゴンより高い場合は何もしない
                if (!(isHitRoof && minY < lineResult.Position.y))
                {
                    // ポリゴンに当たったフラグを立てる
                    isHitRoof = true;

                    // 接触したＹ座標を保存する
                    minY = lineResult.Position.y;
                }
            }
        }

        // 接触したポリゴンがあれば
        if (isHitRoof)
        {
            // 接触した場合はプレイヤーのＹ座標を接触座標を元に更新
            fixedPos.y = minY - HitHeight;
            object.OnHitRoof();
        }
    }
    // 下降中かジャンプ中ではない場合の処理
    else
    {
        bool isHitFloor = false;
        float maxY = 0.0f;

        // 床ポリゴンの数だけ繰り返し
        for (int i = 0; i < floorNum; i++)
        {
            auto poly = floor[i];       // i番目の床ポリゴンのアドレス

            // ジャンプ中かどうかで処理を分岐
            HITRESULT_LINE lineResult;  // 線分とポリゴンとの当たり判定の結果を代入する構造体

            if (object.GetIsJumping())
            {
                // ジャンプ中の場合は頭の先から足先より少し低い位置の間で当たっているかを判定
                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)),
                    VAdd(fixedPos, VGet(0.0f, -0.1f, 0.0f)),
                    poly->Position[0], poly->Position[1], poly->Position[2]);
            }
            else
            {
                // 走っている場合は頭の先からそこそこ低い位置の間で当たっているかを判定( 傾斜で落下状態に移行してしまわない為 )
                lineResult = HitCheck_Line_Triangle(VAdd(fixedPos, VGet(0.0f, HitHeight, 0.0f)),
                    VAdd(fixedPos, VGet(0.0f, -0.5f, 0.0f)),
                    poly->Position[0], poly->Position[1], poly->Position[2]);
            }

            // 既に当たったポリゴンがあり、且つ今まで検出した床ポリゴンより低い場合は何もしない
            if (lineResult.HitFlag)
            {
                if (!(isHitFloor && maxY > lineResult.Position.y))
                {
                    // 接触したＹ座標を保存する
                    isHitFloor = true;
                    maxY = lineResult.Position.y;
                }
            }
        }

        // 床ポリゴンに当たった
        if (isHitFloor)
        {
            // 接触したポリゴンで一番高いＹ座標をプレイヤーのＹ座標にする
            fixedPos.y = maxY;

            // 床に当たった時
            object.OnHitFloor();
        }
        else
        {
            // 床コリジョンに当たっていなくて且つジャンプ状態ではなかった場合は落下状態
            object.OnFall();
        }
    }

    return fixedPos;
}