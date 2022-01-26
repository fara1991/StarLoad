#include "BaseScene.h"

BaseScene::BaseScene(ISceneManager* pChanger, IResourceManager* pResource)
{
	m_pSceneChanger = pChanger;
	m_pResource = pResource;

	if(m_pAnime == nullptr) m_pAnime = new Animation();
	if(m_pKey == nullptr) m_pKey = new Keyboard();
}

BaseScene::~BaseScene()
{
	DeletePtr(m_pKey);
	DeletePtr(m_pAnime);
}

/// <summary>
/// ����������
/// </summary>
void BaseScene::Initialize(){
	//�t�@�C���`�F�b�N�����A�Ȃ���΃f�t�H���g�l���쐬����
	InitializeLoadConfigStream();
	InitializeLoadResultStream();

	m_pAnime->Initialize();
	m_pKey->Initialize();
}

/// <summary>
/// �X�V����
/// </summary>
void BaseScene::Update(){
	m_pAnime->Update();
	m_pKey->Update();
}

/// <summary>
/// �`�揈��
/// </summary>
void BaseScene::DrawLoop(){
	m_pAnime->DrawLoop();
	m_pKey->DrawLoop();
}

/// <summary>
/// �I������
/// </summary>
void BaseScene::Finalize(){
	FinalizeLoadConfigStream();
	FinalizeLoadResultStream();

	m_pAnime->Finalize();
	m_pKey->Finalize();
}

/// <summary>
/// Config.json�t�@�C����ǂݍ��݁A���ʐݒ�ɔ��f���܂��B
/// �t�@�C�����Ȃ�����j�����Ă���Ƃ��́A�V����json�t�@�C�����쐬���A�����l���������݂܂��B
/// </summary>
void BaseScene::InitializeLoadConfigStream(){
	int nBGMVolume = 0;
	int nSEVolume = 0;
	try
	{
		m_fStream.close();
		m_fStream.clear();
		m_fStream.open(m_sConfigFileName, std::ios_base::in);
		if(m_fStream.fail()) throw std::exception();

		//�f�[�^�ǂݍ���
		std::string sJsonWord;
		std::string line;
		while(std::getline(m_fStream, line)) sJsonWord += line;

		std::string sErr;
		auto jsonConfig = json11::Json::parse(sJsonWord, sErr);
		if(!sErr.empty()) throw std::exception();
		if(!jsonConfig["BGM"].is_number()) throw std::exception();
		if(!jsonConfig["SE"].is_number()) throw std::exception();

		nBGMVolume = jsonConfig["BGM"].int_value();
		nSEVolume = jsonConfig["SE"].int_value();
		SetGameDataVolumeBGM(nBGMVolume);
		SetGameDataVolumeSE(nSEVolume);
	}
	catch(...)
	{
		//�G���[�̏ꍇ��Json�V�K�쐬���āA�ݒ菉���f�[�^����������
		m_fStream.close();
		m_fStream.clear();
		m_fStream.open(m_sConfigFileName, std::ios_base::out);
		m_fStream << JsonConfigData.dump() << std::endl;
		nBGMVolume = JsonConfigData["BGM"].int_value();
		nSEVolume = JsonConfigData["SE"].int_value();
		SetGameDataVolumeBGM(nBGMVolume);
		SetGameDataVolumeSE(nSEVolume);
	}
	m_fStream.close();
	m_pResource->SetSoundsBGMVolume(nBGMVolume);
	m_pResource->SetSoundsSEVolume(nSEVolume);
}

/// <summary>
/// Result.json�t�@�C����ǂݍ��݁A���ʂɔ��f���܂��B
/// �t�@�C�����Ȃ�����j�����Ă���Ƃ��́A�V����json�t�@�C�����쐬���A�����l���������݂܂��B
/// </summary>
void BaseScene::InitializeLoadResultStream(){
	const int nResultNum = 3;
	std::string asLevel[nResultNum] = { "Begginer", "Standard", "Hard" };
	try
	{
		m_fStream.close();
		m_fStream.clear();
		m_fStream.open(m_sResultFileName, std::ios_base::in);
		if(m_fStream.fail()) throw std::exception();
		//�f�[�^�ǂݍ���
		std::string sJsonWord;
		std::string line;
		while(std::getline(m_fStream, line)) sJsonWord += line;

		std::string sErr;
		auto jsonResult = json11::Json::parse(sJsonWord, sErr);
		if(!sErr.empty()) throw std::exception();

		for(int i = 0; i < nResultNum; i++){
			auto jsonKey = jsonResult[asLevel[i]];
			if(jsonKey.is_null()) throw std::exception();
			if(jsonKey["DateTime"].is_null() || jsonKey["Score"].is_null() || jsonKey["Rank"].is_null()) throw std::exception();

			auto sDatetime = jsonKey["DateTime"].string_value();
			if(!EnableConvertDateTime(sDatetime)) throw std::exception();
			if(!jsonKey["Score"].is_number() || jsonKey["Score"] < 0) throw std::exception();
			if(!jsonKey["Rank"].is_string()) throw std::exception();
			
			//�����N�Ή��̕������`�F�b�N
			std::string sRank = jsonKey["Rank"].string_value();
			std::string sSearch = "SABCD";
			if(sSearch.find(sRank) == Invalid) std::exception();
		}
		for(int i = 0; i < nResultNum; i++){
			auto jsonKey = jsonResult[asLevel[i]];
			SetGameDataDateTime(i, jsonKey["DateTime"].string_value());
			SetGameDataScore(i, jsonKey["Score"].int_value());
			SetGameDataRank(i, jsonKey["Rank"].string_value());
		}
	}
	catch(...)
	{
		m_fStream.close();
		m_fStream.clear();
		m_fStream.open(m_sResultFileName, std::ios_base::out);
		m_fStream << JsonResultData.dump() << std::endl;
		for(int i = 0; i < nResultNum; i++){
			auto jsonKey = JsonResultData[asLevel[i]];
			SetGameDataDateTime(i, jsonKey["DateTime"].string_value());
			SetGameDataScore(i, jsonKey["Score"].int_value());
			SetGameDataRank(i, jsonKey["Rank"].string_value());
		}
	}
	m_fStream.close();
}

/// <summary>
/// �w��̕����񂪓��t���ǂ������`�F�b�N���܂��B
/// </summary>
/// <param name="sDatetime">�Ώە�����</param>
/// <returns>���t�`��(YYYY/mm/dd HH:ii:ss)���ǂ���</returns>
int BaseScene::EnableConvertDateTime(std::string sDatetime){
	time_t tNow = time(nullptr);
	tm tStruct;
	localtime_s(&tStruct, &tNow);
	int bConvert = TRUE;
	try
	{
		//YYYY/mm/dd HH:ii:ss�̌`�����`�F�b�N
		if(sDatetime.find("/") != 4) throw std::exception();
		if(sDatetime.find("/", 5) != 7) throw std::exception();
		if(sDatetime.find(" ") != 10) throw std::exception();
		if(sDatetime.find(":") != 13) throw std::exception();
		if(sDatetime.find(":", 14) != 16) throw std::exception();

		//�\���̂ł͔N��1900�N����̒ʎZ�N�A���͎��ۂ̌�-1���ꂽ�l�ɂȂ��Ă���
		tStruct.tm_year = std::stoi(sDatetime.substr(0, 4)) - 1900;
		tStruct.tm_mon = std::stoi(sDatetime.substr(5, 2)) - 1;
		tStruct.tm_mday = std::stoi(sDatetime.substr(8, 3));
		tStruct.tm_hour = std::stoi(sDatetime.substr(11, 2));
		tStruct.tm_min = std::stoi(sDatetime.substr(14, 2));
		tStruct.tm_sec = std::stoi(sDatetime.substr(17, 2));
		if(mktime(&tStruct) == Invalid) throw std::exception();
	}
	catch(const std::exception&){ bConvert = FALSE; }
	return bConvert;
}

/// <summary>
/// Config.json�t�@�C���ɉ��ʏ����������݂܂��B
/// </summary>
void BaseScene::FinalizeLoadConfigStream(){
	json11::Json JsonSaveConfigData = json11::Json::object{
		{ "BGM", GetGameDataVolumeBGM() },
		{ "SE", GetGameDataVolumeSE() }
	};
	m_fStream.clear();
	m_fStream.open(m_sConfigFileName, std::ios_base::out);
	m_fStream << JsonSaveConfigData.dump() << std::endl;
	m_fStream.close();
}

/// <summary>
/// Result.json�t�@�C���Ɍ��ʏ����������݂܂��B
/// </summary>
void BaseScene::FinalizeLoadResultStream(){
	json11::Json JsonSaveResultData = json11::Json::object{
		{
			"Begginer", json11::Json::object{
				{ "DateTime", GetGameDataDateTime(static_cast<int>(LEVEL_BEGINNER)).c_str() },
				{ "Score", GetGameDataScore(static_cast<int>(LEVEL_BEGINNER)) },
				{ "Rank", GetGameDataRank(static_cast<int>(LEVEL_BEGINNER)).c_str() }
			}
		},
		{
			"Standard", json11::Json::object{
				{ "DateTime", GetGameDataDateTime(static_cast<int>(LEVEL_STANDARD)).c_str() },
				{ "Score", GetGameDataScore(static_cast<int>(LEVEL_STANDARD)) },
				{ "Rank", GetGameDataRank(static_cast<int>(LEVEL_STANDARD)).c_str() }
			}
		},
		{
			"Hard", json11::Json::object{
				{ "DateTime", GetGameDataDateTime(static_cast<int>(LEVEL_HARD)).c_str() },
				{ "Score", GetGameDataScore(static_cast<int>(LEVEL_HARD)) },
				{ "Rank", GetGameDataRank(static_cast<int>(LEVEL_HARD)).c_str() }
			}
		}
	};
	m_fStream.clear();
	m_fStream.open(m_sResultFileName, std::ios_base::out);
	m_fStream << JsonSaveResultData.dump() << std::endl;
	m_fStream.close();
}

/// <summary>
/// ���ݎ��Ԃ̕�������擾���܂��B
/// </summary>
/// <returns>���ݎ��Ԃ̕�����</returns>
std::string BaseScene::GetNowDateTime(){
	//���ݎ��Ԃ����̂܂ܕ�����
	time_t tNow = time(nullptr);
	tm tStruct;
	localtime_s(&tStruct, &tNow);
	std::string sYear = std::to_string(tStruct.tm_year + 1900);
	std::string sMonth = std::to_string(tStruct.tm_mon + 1);
	std::string sDay = std::to_string(tStruct.tm_mday);
	std::string sHour = std::to_string(tStruct.tm_hour);
	std::string sMinute = std::to_string(tStruct.tm_min);
	std::string sSecond = std::to_string(tStruct.tm_sec);
	if(sMonth.size() == 1) sMonth = "0" + sMonth;
	if(sDay.size() == 1) sDay = "0" + sDay;
	if(sHour.size() == 1) sHour = "0" + sHour;
	if(sMinute.size() == 1) sMinute = "0" + sMinute;
	if(sSecond.size() == 1) sSecond = "0" + sSecond;
	std::string sDateTime = sYear + "/" + sMonth + "/" + sDay + " " + sHour + ":" + sMinute + ":" + sSecond;
	return sDateTime;
}