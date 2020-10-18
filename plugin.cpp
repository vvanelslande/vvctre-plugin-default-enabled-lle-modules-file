// Copyright 2020 Valentin Vanelslande
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#include <fstream>
#include <iostream>

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

VVCTRE_PLUGIN_EXPORT void PluginLoaded(void* core, void* plugin_manager_,
                                       void* required_functions[]) {
    vvctre_settings_set_use_lle_module = (vvctre_settings_set_use_lle_module_t)required_functions[0];
}

VVCTRE_PLUGIN_EXPORT void InitialSettingsOpening() {
    std::ifstream file("enabled-lle-modules.txt");
    if (!file.fail()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                vvctre_settings_set_use_lle_module(line.c_str(), true);
            }
        }
    }
}
