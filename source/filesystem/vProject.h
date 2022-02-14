#pragma once

// filesystem

#include "filesystem/vDirectory.h"

// entity

#include "entity/vScene.h"

// std

#include <filesystem>



namespace vaxe
{
    class vProject
    {
    public:
        vProject();
        ~vProject();

        std::shared_ptr<vScene> GetCurrentScene() { return m_currentScene; }
        std::shared_ptr<vDirectory> GetCurrentDirectory() { return m_currentDirectory; }

        std::shared_ptr<vDirectory> CreateSubDirectoryInCurrentDirectory(std::string name);

        void SetNewDirectory(std::shared_ptr<vDirectory> newDirectory) { m_currentDirectory = newDirectory; }
        void GoUpDirectory() { if (!CurrentDirectoryIsRoot()) m_currentDirectory = m_currentDirectory->GetParentDirectory(); }
        bool CurrentDirectoryIsRoot() { return (m_currentDirectory->GetRelativePath() == ""); }

        bool SaveProject();

    private:

        bool LoadConfigFile();
        bool CreateNewConfigFile();

        void IterateThroughDirectory(std::shared_ptr<vDirectory> directory);

        std::shared_ptr<vDirectory> CreateDirectory(std::shared_ptr<vDirectory> directory, std::string name);

        pugi::xml_document doc;

        std::string m_path = "C:\\Vaxe2D\\TestProject";
        std::shared_ptr<vScene> m_currentScene;
        std::shared_ptr<vDirectory> m_currentDirectory;
        
    };
}