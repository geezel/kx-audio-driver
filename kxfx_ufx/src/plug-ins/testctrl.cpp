
#include "stdafx.h"
#include "../kxuniform.h"
#include "testctrlview.h"
#include "testctrl.h"

//.....................................................................................

// include dsp data generated by kX Editor from Dane code
#include "testctrl_dsp.cpp" 

// combine dsp data declared in testctrl_dsp.cpp into single 'dsp_pgm_data' structure,
// second argument ('testctrl') should be exactly the same as prefixes in testctrl_dsp.cpp
DECLARE_DSP_PROGRAM(dsp_pgm_data, testctrl); 

//.....................................................................................

int testctrl_entry(int command, dword *ret)										
{																						
	switch(command)																		
	{																					
	case KXPLUGIN_GET_NAME:		 // title of plugin to be shown in menus, kx dsp etc.
		lstrcpyn((char*) ret, dsp_pgm_data.strings[0], KX_MAX_STRING);						
  		return 0;																		
	case KXPLUGIN_GET_GUID:		 // guid to identify plugin							
		lstrcpyn((char*) ret, dsp_pgm_data.strings[5], KX_MAX_STRING);						
  		return 0;																		
	case KXPLUGIN_INSTANTIATE:	 // actual request to create plugin					
		*ret = (dword) new Testctrl;												
		return 0;																		
	default:																			
		*ret = NULL;																	
		return 1;																		
	}															
}

//.....................................................................................

// factory presets
typedef kxparam_t const preset[params_count + 1];
#define P (kxparam_t)

preset factory_presets[] = 
{
	{P "Reset", 0, 0, 0, 0},
	{P "Left Only", 0, 0, 0, -100},
	{P "Right Only", 0, 0, 0, 100},
	{P "Half Level", 0, 0, -60, 0},
};

const int presets_count = (sizeof factory_presets / sizeof preset);

// parameter descriptions (name, min and max value)
const kx_fxparam_descr param_descr[params_count] = 
{
	{"Bypass", NULL, 0, 1},
	{"Mute",   NULL, 0, 1},
	{"Level", NULL, -600, 0},
	{"Pan",   NULL, -100, 100},
};

//.....................................................................................

Testctrl::Testctrl()
{
	set_options(UP_HAS_VIEW);
	set_dsp_pgm((kx_dsp_pgm*) &dsp_pgm_data);

	/* it is recommended you to set atleast one factory preset,
	   preset declared first is used as default until
	   you specify "[Default]" one directly */
	set_factory_presets(presets_count, params_count, factory_presets); 

	ZM(params);
}

int Testctrl::get_param_count()
{
	return params_count;
}

int Testctrl::describe_param(int id, kx_fxparam_descr *descr)
{
	memcpy(descr, &param_descr[id], sizeof kx_fxparam_descr); 
	return 0;
}

int Testctrl::get_param(int id, kxparam_t *value)
{
	*value = params[id]; 
	return 0;
}

int Testctrl::set_param(int id, kxparam_t value)
{
	params[id] = value;

	switch (id)
	{
		case ID_BYPASS:
			id = id;
			break;
		case ID_MUTE:
			id = id;
			break;
		case ID_LEVEL:
			id = id;
			break;
		case ID_PAN:
			id = id;
			break;
	}

	post_param_changed(id, value); // send parameter change notification to pluginview

	return 0;
}

//.....................................................................................

uPluginView* Testctrl::create_view()
{
	uPluginView* pv = (uPluginView*) new TestctrlView(this);
	return pv;
}
