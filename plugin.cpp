// Copyright 2020 Valentin Vanelslande
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <fstream>
#include <iostream>
#include <string>

#include <whereami.h>

#include "string_util.h"

#ifdef _WIN32
#define VVCTRE_PLUGIN_EXPORT extern "C" __declspec(dllexport)
#else
#define VVCTRE_PLUGIN_EXPORT extern "C"
#endif

static const char* required_function_name = "vvctre_settings_set_use_lle_module";

typedef void (*vvctre_settings_set_use_lle_module_t)(const char* name, bool value);
static vvctre_settings_set_use_lle_module_t vvctre_settings_set_use_lle_module;

VVCTRE_PLUGIN_EXPORT int GetRequiredFunctionCount() {
    return 1;
}

VVCTRE_PLUGIN_EXPORT const char** GetRequiredFunctionNames() {
    return &required_function_name;
}

VVCTRE_PLUGIN_EXPORT void PluginLoaded(void* core, void* plugin_manager,
                                       void* required_functions[]) {
    vvctre_settings_set_use_lle_module =
        (vvctre_settings_set_use_lle_module_t)required_functions[0];
}

VVCTRE_PLUGIN_EXPORT void InitialSettingsOpening() {
    int length = wai_getExecutablePath(nullptr, 0, nullptr);
    std::string vvctre_folder(length, '\0');
    int dirname_length = 0;
    wai_getExecutablePath(&vvctre_folder[0], length, &dirname_length);
    vvctre_folder = vvctre_folder.substr(0, dirname_length);

    std::ifstream file;
#ifdef _MSC_VER
    file.open(Common::UTF8ToUTF16W(vvctre_folder + "\\default-enabled-lle-modules.txt"));
#else
    file.open(vvctre_folder + "/default-enabled-lle-modules.txt");
#endif
    if (!file.fail()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                vvctre_settings_set_use_lle_module(line.c_str(), true);
            }
        }
    }
}
