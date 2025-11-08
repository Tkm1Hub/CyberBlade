#include <vector>
#include <memory>

class UIBase;
class UIManager
{
private:
	// コンストラクタを非公開にする
	UIManager() {}

	// コピーコンストラクタと代入演算子を削除
	UIManager(const UIManager&) = delete;
	UIManager& operator=(const UIManager&) = delete;

	//プライベートデストラクタ
	~UIManager() {}
public:
	// インスタンスを取得するためのメソッド
	static UIManager& GetUIManager()
	{
		static UIManager instance;      // 静的変数としてインスタンスを定義
		return instance;
	}

	void AddUI(std::shared_ptr<UIBase> ui);
	void Update();
	void Draw();

private:
	std::vector<std::shared_ptr<UIBase>> m_uiList;
};