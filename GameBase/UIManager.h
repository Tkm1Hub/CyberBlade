#include <vector>
#include <memory>

class UIBase;
class IGameObject;
class Marker;
class Player;
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
	void Init();
	void SetObjects(std::vector<std::weak_ptr<IGameObject>> owners) { m_objects = owners; }
	void SetPlayer(const std::weak_ptr<Player>& player) { m_pPlayer = player; }
	void Update();
	void Draw();

	const std::vector<std::shared_ptr<UIBase>>& GetUIList() { return m_uiList; }
	
private:
	std::vector<std::shared_ptr<UIBase>> m_uiList;
	std::vector < std::weak_ptr<IGameObject>> m_objects;
	std::weak_ptr<Player> m_pPlayer;
	std::shared_ptr<Marker> marker;
};