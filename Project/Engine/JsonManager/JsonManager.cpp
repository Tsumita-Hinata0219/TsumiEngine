#include "JsonManager.h"



// 初期化処理
void JsonManager::Initialize()
{
	// モデルマネージャーのインスタンスの取得
	modelManager_ = ModelManager::GetInstance();

	levelData_ = std::make_unique<LevelData>();

}


// 解放処理
void JsonManager::Finalize() {}


// Jsonファイルの読み込み
void JsonManager::LoadSceneFile(const std::string& path, const std::string& fileName)
{
	/* ---------- JSOnファイルを読み込んでみる ---------- */

	// 連結してフルパスを得る
	const std::string fullPath = "Resources/" + path + "/" + fileName;

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
	auto levelData = std::make_unique<LevelData>();

	// "objects"の全オブジェクトを走査
	if (deserialized.contains("objects") && deserialized["objects"].is_array()) {

		// 走査してく
		for (nlohmann::json& object : deserialized["objects"]) {

			ScanningObjects(path, object, levelData->objects);
		}
	}


	// とりあえず読み込んだ情報を変数に保存しておく
	levelData_ = move(levelData);
}


// オブジェクトの走査
void JsonManager::ScanningObjects(const std::string& path, nlohmann::json& object, std::map<std::string, std::unique_ptr<LevelData::ObjectData>>& objects)
{
	// 各オブジェクトには必ず "type"データを入れているので
	// "type"が検出できなければ不正として実行を停止する
	assert(object.contains("type"));
	// 種類を取得
	std::string type = object["type"].get<std::string>();


	/* ---------- メッシュの読み込み ---------- */

	// MESH
	if (type.compare("MESH") == 0) {

		// 新しくオブジェクトを作成
		auto objectData = make_unique<LevelData::ObjectData>();


		if (object.contains("type")) {

			// タイプ
			objectData->type = object["type"];
		}
		if (object.contains("file_name")) {

			// ファイル名
			objectData->file_name = object["file_name"];
		}


		// トランスフォームのパラメータ読み込み
		if (object.contains("transform")) {

			nlohmann::json& transform = object["transform"];
			// 平行移動
			objectData->srt.translate.x = (float)transform["translation"][0];
			objectData->srt.translate.y = (float)transform["translation"][2];
			objectData->srt.translate.z = (float)transform["translation"][1];
			// 回転角
			objectData->srt.rotate.x = -(float)transform["rotation"][0] * (float(std::numbers::pi) / 180.0f);
			objectData->srt.rotate.y = -(float)transform["rotation"][2] * (float(std::numbers::pi) / 180.0f);
			objectData->srt.rotate.z = -(float)transform["rotation"][1] * (float(std::numbers::pi) / 180.0f);
			// スケーリング
			objectData->srt.scale.x = (float)transform["scaling"][0];
			objectData->srt.scale.y = (float)transform["scaling"][2];
			objectData->srt.scale.z = (float)transform["scaling"][1];
		}


		// モデルの読み込み
		if (object.contains("load_model")) {
			
			// モデル読み込みのフラグが立っていたら
			if (object["load_model"].is_boolean() && object["load_model"].get<bool>() == true) {

				// ディレクトリ内にある特定の拡張子を持つファイルを取り出す
				std::string directoryPath = path + "/" + objectData->file_name;
				// 最初は.objで走査
				std::string fileName = FindFirstFileWithExtension(directoryPath, ".obj");
				// なければ.gltf
				if (fileName.empty()) {
					fileName = FindFirstFileWithExtension(path, ".gltf");
				}
				// それでもなければエラー
				if (fileName.empty()) {
					Log("ロードするモデルがない");
					assert(0);
				}

				// ディレクトリファイルパスとファイル名からモデルをロードする
				modelManager_->LoadModel(directoryPath, fileName);
			}
		}


		// TODO : コライダーの読み込み



		/* ---------- ツリー構造の走査 ---------- */
		if (object.contains("children") && object["children"].is_array()) {

			for (nlohmann::json& child : object["children"]) {
				ScanningObjects(path, child, objectData->children);
			}
		}

		// オブジェクトを追加
		objects[objectData->file_name] = std::move(objectData);
	}
}


// 読み込んだ情報からモデル作成
void JsonManager::CreateModel()
{
}