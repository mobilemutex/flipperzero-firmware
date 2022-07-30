#include "../infrared_i.h"

typedef enum {
    SubmenuIndexTV1,
    SubmenuIndexTV2,
    SubmenuIndexTV3,
} SubmenuIndex;

static void infrared_scene_universal_tv_select_submenu_callback(void* context, uint32_t index) {
    Infrared* infrared = context;
    view_dispatcher_send_custom_event(infrared->view_dispatcher, index);
}

void infrared_scene_universal_tv_select_on_enter(void* context) {
    Infrared* infrared = context;
    Submenu* submenu = infrared->submenu;

    submenu_add_item(
        submenu,
        "TV1",
        SubmenuIndexTV1,
        infrared_scene_universal_tv_select_submenu_callback,
        context);
    
    submenu_add_item(
        submenu,
        "TV2",
        SubmenuIndexTV2,
        infrared_scene_universal_tv_select_submenu_callback,
        context);
    
    submenu_add_item(
        submenu,
        "TV3",
        SubmenuIndexTV3,
        infrared_scene_universal_tv_select_submenu_callback,
        context);
        
    submenu_set_selected_item(submenu, 0);

    view_dispatcher_switch_to_view(infrared->view_dispatcher, InfraredViewSubmenu);
}

bool infrared_scene_universal_tv_select_on_event(void* context, SceneManagerEvent event) {
    Infrared* infrared = context;
    SceneManager* scene_manager = infrared->scene_manager;
    bool consumed = false;
    InfraredBruteForce* brute_force = infrared->brute_force;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == SubmenuIndexTV1) {
            infrared_brute_force_set_db_filename(brute_force, EXT_PATH("infrared/assets/tv.ir"));
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalTV);
            consumed = true;
        } else if(event.event == SubmenuIndexTV2) {
            infrared_brute_force_set_db_filename(brute_force, EXT_PATH("infrared/assets/tv2.ir"));
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalTV); 
            consumed = true;
        } else if(event.event == SubmenuIndexTV3) {
            infrared_brute_force_set_db_filename(brute_force, EXT_PATH("infrared/assets/tv3.ir"));
            scene_manager_next_scene(scene_manager, InfraredSceneUniversalTV);
            consumed = true;
        }
    }

    return consumed;
}

void infrared_scene_universal_tv_select_on_exit(void* context) {
    Infrared* infrared = context;
    submenu_reset(infrared->submenu);
}
