#include "JsonManager.h"




/// <summary>
/// インスタンスの取得
/// </summary>
JsonManager* JsonManager::GetInstance()
{
	static JsonManager instance;
	return &instance;
}


/// <summary>
/// Jsonファイルの読み込み
/// </summary>
void JsonManager::LoadSceneFile(const std::string& path, const std::string& fileName)
{
	/* ──────────── Jsonファイルを読み込んでみる ──────────── */

	// 連結してフルパスを得る
	const std::string fullPath = "Resources/" + path + "/" + fileName;
	// ファイルストリーム
	std::ifstream file;
	// ファイルを開く
	file.open(fullPath);
	// ファイルオープン失敗をチェック
	if (file.fail()) { assert(0); }


	/* ──────────── ファイルチェック ──────────── */

	// JSON文字列から解凍したデータ
	nlohmann::json deserialized;
	// 解凍
	file >> deserialized;
	// 正しいレベルエディタファイルかチェック
	assert(deserialized.is_object());
	assert(deserialized.contains("name"));
	assert(deserialized["name"].is_string());
	// "name"を文字列として取得
	std::string name = deserialized["name"].get<std::string>();
	// 正しいレベルデータファイルかチェック
	assert(name.compare("scene") == 0);


	/* ──────────── オブジェクトの走査 ──────────── */

	// "objects"の全オブジェクトを走査
	if (deserialized.contains("objects") && deserialized["objects"].is_array()) {

		for (nlohmann::json& object : deserialized["objects"]) {

			// レベルデータ格納用インスタンスを生成
			std::unique_ptr<EntityData> entity = std::make_unique<EntityData>();
			entity = ScanningEntityData(path, object); // 走査

			// 走査した情報をマップコンテナに追加
			AddEntityData(std::move(entity));
		}
	}
}


/// <summary>
/// オブジェクトの走査
/// </summary>
std::unique_ptr<EntityData> JsonManager::ScanningEntityData(const std::string& path, nlohmann::json& object)
{
	std::unique_ptr<EntityData> result = std::make_unique<EntityData>();

	// 各オブジェクトには必ず "type"データを入れているので
	// "type"が検出できなければ不正として実行を停止する
	assert(object.contains("type"));
	// 種類を取得
	std::string type = object["type"].get<std::string>();


	/* ──────────── メッシュの読み込み ──────────── */
	if (type.compare("MESH") == 0) {

		/* ──────────── タイプ ──────────── */
		result->type = ScanningType(object);

		/* ──────────── エンティティネーム ──────────── */
		result->entityName = ScanningEntityName(object);

		/* ──────────── SRT ──────────── */
		result->srt = ScanningSRT(object);

		/* ──────────── コライダーの読み込み ──────────── */
		// TODO

		/* ──────────── プレイヤー情報の読み込み ──────────── */
		result->playerData = ScanningPlayerData(object);

		/* ──────────── エネミー情報の読み込み ──────────── */
		result->enemyData = ScanningEnemyData(object);

		/* ──────────── ツリー構造の走査 ──────────── */
		if (object.contains("children") && object["children"].is_array()) {
			for (nlohmann::json& child : object["children"]) {

				// 新しく子供を作る
				std::unique_ptr<EntityData> childResult = std::make_unique<EntityData>();
				childResult = ScanningEntityData(path, child); // 子供の情報を走査

				// 走査した情報を親に入れる
				result->children[childResult->entityName] = std::move(childResult);
			}
		}
	}

	return std::move(result);
}


/// <summary>
/// タイプ
/// </summary>
std::string JsonManager::ScanningType(nlohmann::json& object)
{
	std::string type{};

	if (object.contains("type")) {

		// タイプ
		type = object["type"];
	}

	return type;
}


/// <summary>
/// エンティティ名
/// </summary>
std::string JsonManager::ScanningEntityName(nlohmann::json& object)
{
	std::string entityName{};

	if (object.contains("name")) {

		// ファイル名
		entityName = object["name"];
	}

	return entityName;
}


/// <summary>
/// SRTの読み込み
/// </summary>
SRT JsonManager::ScanningSRT(nlohmann::json& object)
{
	SRT srt{};

	if (object.contains("transform")) {

		nlohmann::json& transform = object["transform"];
		// 平行移動
		srt.translate.x = (float)transform["translation"][0];
		srt.translate.y = (float)transform["translation"][2];
		srt.translate.z = (float)transform["translation"][1];
		// 回転角
		srt.rotate.x = -(float)transform["rotation"][0] * (float(std::numbers::pi) / 180.0f);
		srt.rotate.y = -(float)transform["rotation"][2] * (float(std::numbers::pi) / 180.0f);
		srt.rotate.z = -(float)transform["rotation"][1] * (float(std::numbers::pi) / 180.0f);
		// スケーリング
		srt.scale.x = (float)transform["scaling"][0];
		srt.scale.y = (float)transform["scaling"][2];
		srt.scale.z = (float)transform["scaling"][1];
	}

	return srt;
}


/// <summary>
/// PlayerDataの読み込み
/// </summary>
EntityPlayerData JsonManager::ScanningPlayerData(nlohmann::json& object)
{
	EntityPlayerData result{};

	if (object.contains("category")) {

		nlohmann::json& category = object["category"];

		// typeがPlayerでなければ終了
		if (category["type"] != "PLAYER") { return result; }

	}

	return result;
}


/// <summary>
/// EnemyDataの読み込み
/// </summary>
EntityEnemyData JsonManager::ScanningEnemyData(nlohmann::json& object)
{
	EntityEnemyData result{};

	if (object.contains("category")) {

		nlohmann::json& category = object["category"];

		// typeがEnemyでなければ終了
		if (category["type"] != "ENEMY") { return result; }

		// 射撃方向
		if (category["shot_direction"] == "FORWARD") {
			result.direction = EnemyExecuteShot::Direction::Forward;
		}
		else if (category["shot_direction"] == "TRIPLE_FORWARD") {
			result.direction = EnemyExecuteShot::Direction::TripleForward;
		}
		else if (category["shot_direction"] == "CROSS") {
			result.direction = EnemyExecuteShot::Direction::Cross;
		}
		else if (category["shot_direction"] == "OMNI_FOUR") {
			result.direction = EnemyExecuteShot::Direction::Omni_Four;
		}
		else if (category["shot_direction"] == "OMNI_FIVE") {
			result.direction = EnemyExecuteShot::Direction::Omni_Five;
		}
		else if (category["shot_direction"] == "OMNI_EIGHT") {
			result.direction = EnemyExecuteShot::Direction::Omni_Eight;
		}
		else if (category["shot_direction"] == "RANDOM") {
			result.direction = EnemyExecuteShot::Direction::Random;
		}

		// バレットタイプ
		if (category["bullet_behavior"] == "COMMON") {
			result.behavior = EnemyExecuteShot::BulletBehavior::Common;
		}
		else if (category["bullet_behavior"] == "RESISTANT") {
			result.behavior = EnemyExecuteShot::BulletBehavior::Resistant;
		}
		else if (category["bullet_behavior"] == "RANDOM") {
			result.behavior = EnemyExecuteShot::BulletBehavior::Random;
		}

		// 射撃間隔
		result.shotInterval = (float)category["shoot_interval"];
	}

	return result;
}

