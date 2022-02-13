#include "filesystem/vProject.h"

namespace vaxe
{
    vProject::vProject()
    {
        m_currentScene = std::make_shared<vScene>();
        

        if (!LoadConfigFile())
        {
            CreateNewConfigFile();
        }
    }

    vProject::~vProject()
    {

    }

    bool vProject::LoadConfigFile()
    {
        pugi::xml_parse_result result = doc.load_file((m_path + "/vconfig.xml").c_str());

        if (!result)
        {
            return 0;
        }

        m_currentDirectory = std::make_shared<vDirectory>(m_path, "", "Base", doc.child("Hierarchy"));

        return 1;
    }

    bool vProject::CreateNewConfigFile()
    {
        m_currentDirectory = std::make_shared<vDirectory>(m_path, "", "Base", doc.append_child("Hierarchy"));
        
        auto audioDir = CreateDirectory(m_currentDirectory, "Audio");
        CreateDirectory(m_currentDirectory, "Fonts");
        CreateDirectory(m_currentDirectory, "Scenes");
        CreateDirectory(m_currentDirectory, "Scripts");
        CreateDirectory(m_currentDirectory, "Textures");

        CreateDirectory(audioDir, "Music");
        CreateDirectory(audioDir, "SoundEffects");

        return doc.save_file((m_path + "/vconfig.xml").c_str());

    }

    std::shared_ptr<vDirectory> vProject::CreateDirectory(std::shared_ptr<vDirectory> directory, std::string name)
    {
        std::string relativePath = directory->GetRelativePath() + "/" + name;
        std::string basePath = m_path + relativePath;
        std::filesystem::create_directory(basePath);

        return directory->AddSubDirectory(basePath, relativePath, name);
    }
}