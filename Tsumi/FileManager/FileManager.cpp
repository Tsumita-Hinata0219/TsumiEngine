#include "FileManager.h"



// 初期化処理
void FileManager::Initialize()
{
	levelData_ = make_unique<LevelData>();
}


// 終了処理
void FileManager::BeginFrame() {}


// 終了処理
void FileManager::EndFrame() {}


// 解放処理
void FileManager::Finalize() {}


// JSONファイル読み込み
void FileManager::LoadJsonFile(const std::string& routeFilePath, const std::string& fileName)
{
	/* ---------- JSOnファイルを読み込んでみる ---------- */

	// 連結してフルパスを得る
	const std::string fullPath = routeFilePath + fileName + ".json";

	// ファイルストリーム
	std::ifstream file;

	// ファイルを開く
	file.open(fullPath);
	// ファイルオープン失敗をチェック
	if (file.fail()) {
		assert(0);
	}


	/* ---------- ファイルチェック ---------- */

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


	/* ---------- オブジェクトの走査 ---------- */

	// レベルデータ格納用インスタンスを生成
	unique_ptr<LevelData> levelData = make_unique<LevelData>();

	// "objects"の全オブジェクトを走査
	if (deserialized.contains("objects") && deserialized["objects"].is_array()) {

		// 事前にメモリを確保しておく
		levelData->objects.reserve(deserialized["objects"].size());

		// 走査してく
		for (nlohmann::json& object : deserialized["objects"]) {

			ScanningObjects(object, levelData.get());
		}
	}


	// とりあえず読み込んだ情報を変数に保存しておく
	levelData_ = move(levelData);
}


// オブジェクトの走査
void FileManager::ScanningObjects(nlohmann::json& object, LevelData* levelData)
{
	// 各オブジェクトには必ず "type"データを入れているので
	// "type"が検出できなければ不正として実行を停止する
	assert(object.contains("type"));
	// 種類を取得
	std::string type = object["type"].get<std::string>();


	/* ---------- メッシュの読み込み ---------- */

	// MESH
	if (type.compare("MESH") == 0) {

		// 要素追加
		levelData->objects.emplace_back(LevelData::ObjectData{});
		// 今追加した要素の参照を得る
		LevelData::ObjectData& objectData = levelData->objects.back();

		if (object.contains("file_name")) {

			// ファイル名
			objectData.file_name = object["file_name"];
		}

		// トランスフォームのパラメータ読み込み
		nlohmann::json& transform = object["transform"];
		// 平行移動
		objectData.translation.x = (float)transform["translation"][1];
		objectData.translation.y = (float)transform["translation"][2];
		objectData.translation.z = (float)transform["translation"][0];
		// 回転角
		objectData.rotation.x = -(float)transform["rotation"][1];
		objectData.rotation.y = -(float)transform["rotation"][2];
		objectData.rotation.z = (float)transform["rotation"][0];
		// スケーリング
		objectData.scaling.x = (float)transform["scaling"][1];
		objectData.scaling.y = (float)transform["scaling"][2];
		objectData.scaling.z = (float)transform["scaling"][0];


		// TODO : コライダーの読み込み

	}


	/* ---------- ツリー構造の走査 ---------- */

	// 子オブジェクトの走査時に、"children"フィールドが存在し、かつ配列であることの確認
	if (object.contains("children") && object["children"].is_array()) {
		for (nlohmann::json& child : object["children"]) {
			ScanningObjects(child, levelData);
		}
	}
}


