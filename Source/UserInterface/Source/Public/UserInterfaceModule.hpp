// Author: Lucas Vilas-Boas
// Year : 2024
// Repo : https://github.com/lucoiso/vk-imgui-template-project

#ifndef USERINTERFACEMODULE_H
#define USERINTERFACEMODULE_H

#ifdef BUILD_DLL
#define USERINTERFACEMODULE_API _declspec(dllexport)
#else
#define USERINTERFACEMODULE_API _declspec(dllimport)
#endif
#endif
