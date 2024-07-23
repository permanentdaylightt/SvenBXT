#ifdef VIEW_H_RECURSE_GUARD
#error Recursive header files inclusion detected in view.h
#else //VIEW_H_RECURSE_GUARD

#define VIEW_H_RECURSE_GUARD

#ifndef VIEW_H_GUARD
#define VIEW_H_GUARD
#pragma once

#ifdef __cplusplus

extern ref_params_s g_RefParams;
void HOOKED_V_CalcRefdef(struct ref_params_s* pparams);

#else //!__cplusplus
#error C++ compiler required to compile view.h
#endif //__cplusplus

#endif //VIEW_H_GUARD

#undef VIEW_H_RECURSE_GUARD
#endif //VIEW_H_RECURSE_GUARD