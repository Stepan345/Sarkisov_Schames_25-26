#include "main.h"
// styles
namespace selector{
	int autonColor = 0;
	int autonType = 0;
	bool autonStarted = false;
	// extern bool autonStarted = false;
	lv_style_t redREL;

	lv_style_t redPRE;
	lv_style_t redSEL;

	lv_style_t blueREL;
	lv_style_t bluePRE;
	lv_style_t blueSEL;

	lv_style_t btnREL;
	lv_style_t btnPRE;
	lv_style_t btnSEL;

	lv_style_t skillsREL;
	lv_style_t skillsPRE;
	lv_style_t skillsSEL;

	lv_obj_t * red;
	lv_obj_t * blue;
	lv_obj_t * skills;

	lv_obj_t * startAuton;
	lv_obj_t * A1;//Goal Adjacent
	auto A1Tag = "Win Point";
	lv_obj_t * A2;//Mid-Field
	auto A2Tag = "Goal Rush";
	lv_obj_t * A3;//Anti-Auton
	auto A3Tag = "Nothing";

	lv_obj_t * speedSlider;
	lv_obj_t * turnSlider;

	lv_obj_t * speedLabel;
	lv_obj_t * turnLabel;
	

	//buttons



	void selectAlliance(lv_event_t * e){
		lv_event_code_t code = lv_event_get_code(e);
		lv_obj_t * btn = lv_event_get_target(e);
		if(code == LV_EVENT_CLICKED && btn == blue){
			lv_obj_remove_style(blue,&redREL,0);
			lv_obj_add_style(blue,&blueSEL,0);
			lv_obj_remove_style(red,&redSEL,0);
			lv_obj_add_style(red,&redREL,0);
			lv_obj_remove_style(skills,&skillsSEL,0);
			lv_obj_add_style(skills,&skillsREL,0);
			autonColor = 1;
		}else if(code == LV_EVENT_CLICKED && btn == red){
			lv_obj_remove_style(red,&redREL,0);
			lv_obj_add_style(red,&redSEL,0);
			lv_obj_remove_style(blue,&blueSEL,0);
			lv_obj_add_style(blue,&blueREL,0);
			lv_obj_remove_style(skills,&skillsSEL,0);
			lv_obj_add_style(skills,&skillsREL,0);
			autonColor = 0;
		}else if(code == LV_EVENT_CLICKED && btn == skills){
			lv_obj_remove_style(skills,&skillsREL,0);
			lv_obj_add_style(skills,&skillsSEL,0);
			lv_obj_remove_style(blue,&blueSEL,0);
			lv_obj_add_style(blue,&blueREL,0);
			lv_obj_remove_style(red,&redSEL,0);
			lv_obj_add_style(red,&redREL,0);
			autonColor = 2;
		}
	}
	void selectType(lv_event_t * e){
		lv_event_code_t code = lv_event_get_code(e);
		lv_obj_t * btn = lv_event_get_target(e);
		if(btn == A1){
			lv_obj_remove_style(A1,&btnREL,0);
			lv_obj_add_style(A1,&btnSEL,0);
			lv_obj_remove_style(A2,&btnSEL,0);
			lv_obj_add_style(A2,&btnREL,0);
			lv_obj_remove_style(A3,&btnSEL,0);
			lv_obj_add_style(A3,&btnREL,0);
			autonType = 0;
		}else if(btn == A2){
			lv_obj_remove_style(A2,&btnREL,0);
			lv_obj_add_style(A2,&btnSEL,0);
			lv_obj_remove_style(A1,&btnSEL,0);
			lv_obj_add_style(A1,&btnREL,0);
			lv_obj_remove_style(A3,&btnSEL,0);
			lv_obj_add_style(A3,&btnREL,0);
			autonType = 1;
		}else if(btn == A3){
			lv_obj_remove_style(A3,&btnREL,0);
			lv_obj_add_style(A3,&btnSEL,0);
			lv_obj_remove_style(A2,&btnSEL,0);
			lv_obj_add_style(A2,&btnREL,0);
			lv_obj_remove_style(A1,&btnSEL,0);
			lv_obj_add_style(A1,&btnREL,0);
			autonType = 2;
		}
	}
	void clearScreen(){
		Controller Controller1(E_CONTROLLER_MASTER);
		Controller1.set_text(0,0,"screen cleared");
		lv_obj_clean(lv_scr_act());
		lv_obj_t * plate = lv_label_create(lv_scr_act());
		lv_label_set_text(plate,
" _________________ _____  _____    ___ \n"
"|  ___| ___ \\ ___ \\  ___||  _  |  /   |\n"
"| |__ | |_/ / |_/ /___ \\ | |/' | / /| |\n"
"|  __||    /|    /    \\ \\|  /| |/ /_| |\n"
"| |___| |\\ \\| |\\ \\/\\__/ /\\ |_/ /\\___  |\n"
"\\____/\\_| \\_\\_| \\_\\____/  \\___/     |_/");
		lv_style_set_text_font(&blueREL,&lv_font_unscii_8);
		lv_style_set_text_font(&redREL,&lv_font_unscii_8);
		lv_style_set_text_font(&skillsREL,&lv_font_unscii_8);
		lv_obj_center(plate);
		if(autonColor == 0)lv_obj_add_style(lv_scr_act(),&redREL,0);
		else if(autonColor == 1)lv_obj_add_style(lv_scr_act(),&blueREL,0);
		else lv_obj_add_style(lv_scr_act(),&skillsREL,0);
	}
	void loadAllianceSelect(){
		red = lv_btn_create(lv_scr_act());
		lv_obj_add_style(red,&redREL,0);
		lv_obj_add_style(red,&redPRE,LV_STATE_PRESSED);
		lv_obj_set_size(red,100,50);
		lv_obj_set_pos(red,5,5);
		lv_obj_t * redLabel = lv_label_create(red);
		lv_label_set_text(redLabel, "Red");
		lv_obj_center(redLabel);
		lv_obj_add_event_cb(red,selectAlliance,LV_EVENT_CLICKED,NULL);
		
		blue = lv_btn_create(lv_scr_act());
		lv_obj_set_size(blue,100,50);
		lv_obj_set_pos(blue,110,5);
		lv_obj_add_style(blue,&blueREL,0);
		lv_obj_add_style(blue,&bluePRE,LV_STATE_PRESSED);
		lv_obj_t * blueLabel = lv_label_create(blue);
		lv_label_set_text(blueLabel, "Blue");
		lv_obj_center(blueLabel);
		lv_obj_add_event_cb(blue,selectAlliance,LV_EVENT_CLICKED,NULL);

		skills = lv_btn_create(lv_scr_act());
		lv_obj_set_size(skills,100,50);
		lv_obj_set_pos(skills,215,5);
		lv_obj_add_style(skills,&skillsREL,0);
		lv_obj_add_style(skills,&skillsPRE,LV_STATE_PRESSED);
		lv_obj_t * skillsLabel = lv_label_create(skills);
		lv_label_set_text(skillsLabel, "Skills");
		lv_obj_center(skillsLabel);
		lv_obj_add_event_cb(skills,selectAlliance,LV_EVENT_CLICKED,NULL);
	}
	void sliderChanged(lv_event_t * e){
		lv_event_code_t code = lv_event_get_code(e);
		lv_obj_t * btn = lv_event_get_target(e);
		if(code == LV_EVENT_VALUE_CHANGED){
			if(btn == speedSlider){
				static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        		snprintf(buf, 4, "%u", lv_slider_get_value(btn));
				lv_label_set_text(speedLabel,buf);
			}else if(btn == turnSlider){
				static char buf[4]; /* max 3 bytes for number plus 1 null terminating byte */
        		snprintf(buf, 4, "%u", lv_slider_get_value(btn));
				lv_label_set_text(turnLabel,buf);
			}
		}
	}
	void loadTypeSelect(){
		A1 = lv_btn_create(lv_scr_act());
		A2 = lv_btn_create(lv_scr_act());
		A3 = lv_btn_create(lv_scr_act());
		lv_obj_add_style(A1,&btnREL,0);
		lv_obj_add_style(A2,&btnREL,0);
		lv_obj_add_style(A3,&btnREL,0);
		lv_obj_add_style(A1,&btnPRE,LV_STATE_PRESSED);
		lv_obj_add_style(A2,&btnPRE,LV_STATE_PRESSED);
		lv_obj_add_style(A3,&btnPRE,LV_STATE_PRESSED);
		lv_obj_set_size(A1,150,75);
		lv_obj_set_size(A2,150,75);
		lv_obj_set_size(A3,150,75);
		lv_obj_set_pos(A1,5,75);
		lv_obj_set_pos(A2,156,75);
		lv_obj_set_pos(A3,307,75);
		lv_obj_t * A1Label = lv_label_create(A1);
		lv_label_set_text(A1Label, A1Tag);
		lv_obj_center(A1Label);
		lv_obj_t * A2Label = lv_label_create(A2);
		lv_label_set_text(A2Label, A2Tag);
		lv_obj_center(A2Label);
		lv_obj_t * A3Label = lv_label_create(A3);
		lv_label_set_text(A3Label, A3Tag);
		lv_obj_center(A3Label);
		lv_obj_add_event_cb(A1,selectType,LV_EVENT_CLICKED,NULL);
		lv_obj_add_event_cb(A2,selectType,LV_EVENT_CLICKED,NULL);
		lv_obj_add_event_cb(A3,selectType,LV_EVENT_CLICKED,NULL);

		lv_obj_t * sliderLabel1 = lv_label_create(lv_scr_act());
		lv_label_set_text(sliderLabel1,"Max Speed");
		speedLabel = lv_label_create(lv_scr_act());
		speedSlider = lv_slider_create(lv_scr_act());
		lv_slider_set_range(speedSlider,30,127);
		lv_slider_set_value(speedSlider,70,LV_ANIM_OFF);
		lv_obj_set_pos(speedSlider,10,175);
		lv_obj_set_width(speedSlider,200);
		lv_obj_add_event_cb(speedSlider,sliderChanged,LV_EVENT_VALUE_CHANGED,0);
		lv_obj_align_to(sliderLabel1,speedSlider,LV_ALIGN_TOP_MID,0,-20);
		lv_obj_align_to(speedLabel,speedSlider,LV_ALIGN_OUT_RIGHT_MID,20,0);
		lv_label_set_text(speedLabel,"70");
		
		lv_obj_t * sliderLabel2 = lv_label_create(lv_scr_act());
		lv_label_set_text(sliderLabel2,"Max Turn Speed");
		turnSlider = lv_slider_create(lv_scr_act());
		turnLabel = lv_label_create(lv_scr_act());
		lv_slider_set_range(turnSlider,30,127);
		lv_slider_set_value(turnSlider,40,LV_ANIM_OFF);
		lv_obj_set_pos(turnSlider,10,200);
		lv_obj_set_width(turnSlider,200);
		lv_obj_add_event_cb(turnSlider,sliderChanged,LV_EVENT_VALUE_CHANGED,0);
		lv_obj_align_to(sliderLabel2,turnSlider,LV_ALIGN_BOTTOM_MID,0,20);
		lv_obj_align_to(turnLabel,turnSlider,LV_ALIGN_OUT_RIGHT_MID,20,0);
		lv_label_set_text(turnLabel,"40");
		
	}
	
	void startAutonomous(lv_event_t * e){
		autonStarted = true;
	}
    void disableDebug(){
        autonStarted = true;
		lv_obj_del(startAuton);
    }

	void screenInit(){
		//init all the styles
		//red
		lv_style_init(&redREL);
		lv_style_set_text_font(&redREL,&lv_font_montserrat_20);
		lv_style_set_bg_color(&redREL,lv_palette_main(LV_PALETTE_RED));
		lv_style_set_text_color(&redREL,lv_color_make(255,255,255));
		lv_style_set_radius(&redREL,1);

		lv_style_init(&redPRE);
		lv_style_set_text_font(&redPRE,&lv_font_montserrat_20);
		lv_style_set_bg_color(&redREL,lv_palette_darken(LV_PALETTE_RED,3));
		lv_style_set_text_color(&redREL,lv_color_make(255,255,255));
		lv_style_set_radius(&redPRE,1);
		
		lv_style_init(&redSEL);
		lv_style_set_text_font(&redSEL,&lv_font_montserrat_20);
		lv_style_set_bg_color(&redSEL,lv_palette_main(LV_PALETTE_RED));
		lv_style_set_text_color(&redSEL,lv_color_make(255,255,255));
		lv_style_set_border_color(&redSEL,lv_color_make(255,255,255));
		lv_style_set_border_width(&redSEL,3);
		lv_style_set_radius(&redSEL,1);

		// //blue
		lv_style_init(&blueREL);
		lv_style_set_text_font(&blueREL,&lv_font_montserrat_20);
		lv_style_set_bg_color(&blueREL,lv_palette_main(LV_PALETTE_BLUE));
		lv_style_set_text_color(&blueREL,lv_color_make(255,255,255));
		lv_style_set_radius(&blueREL,1);

		lv_style_init(&bluePRE);
		lv_style_set_text_font(&bluePRE,&lv_font_montserrat_20);
		lv_style_set_bg_color(&bluePRE,lv_palette_darken(LV_PALETTE_BLUE,3));
		lv_style_set_text_color(&bluePRE,lv_color_make(255,255,255));
		lv_style_set_radius(&bluePRE,1);

		lv_style_init(&blueSEL);
		lv_style_set_text_font(&blueSEL,&lv_font_montserrat_20);
		lv_style_set_bg_color(&blueSEL,lv_palette_main(LV_PALETTE_BLUE));
		lv_style_set_text_color(&blueSEL,lv_color_make(255,255,255));
		lv_style_set_border_color(&blueSEL,lv_color_make(255,255,255));
		lv_style_set_border_width(&blueSEL,3);
		lv_style_set_radius(&blueSEL,1);

		//skills
		lv_style_init(&skillsREL);
		lv_style_set_text_font(&skillsREL,&lv_font_montserrat_20);
		lv_style_set_bg_color(&skillsREL,lv_palette_main(LV_PALETTE_GREEN));
		lv_style_set_text_color(&skillsREL,lv_color_make(255,255,255));
		lv_style_set_radius(&skillsREL,1);

		lv_style_init(&skillsPRE);
		lv_style_set_text_font(&skillsPRE,&lv_font_montserrat_20);
		lv_style_set_bg_color(&skillsPRE,lv_palette_darken(LV_PALETTE_GREEN,3));
		lv_style_set_text_color(&skillsPRE,lv_color_make(255,255,255));
		lv_style_set_radius(&skillsPRE,1);

		lv_style_init(&skillsSEL);
		lv_style_set_text_font(&skillsSEL,&lv_font_montserrat_20);
		lv_style_set_bg_color(&skillsSEL,lv_palette_main(LV_PALETTE_GREEN));
		lv_style_set_text_color(&skillsSEL,lv_color_make(255,255,255));
		lv_style_set_border_color(&skillsSEL,lv_color_make(255,255,255));
		lv_style_set_border_width(&skillsSEL,3);
		lv_style_set_radius(&skillsSEL,1);

		//other buttons
		lv_style_init(&btnREL);
		lv_style_set_text_font(&btnREL,&lv_font_montserrat_16);
		lv_style_set_bg_color(&btnREL,lv_palette_main(LV_PALETTE_GREY));
		lv_style_set_text_color(&btnREL,lv_color_make(50,50,50));
		lv_style_set_radius(&btnREL,1);

		lv_style_init(&btnPRE);
		lv_style_set_text_font(&btnPRE,&lv_font_montserrat_16);
		lv_style_set_bg_color(&btnPRE,lv_palette_darken(LV_PALETTE_GREY,3));
		lv_style_set_text_color(&btnPRE,lv_color_make(255,255,255));
		lv_style_set_radius(&btnPRE,1);

		lv_style_init(&btnSEL);
		lv_style_set_text_font(&btnSEL,&lv_font_montserrat_16);
		lv_style_set_bg_color(&btnSEL,lv_palette_main(LV_PALETTE_GREY));
		lv_style_set_text_color(&btnSEL,lv_color_make(0,0,0));
		lv_style_set_border_color(&btnSEL,lv_color_make(255,255,255));
		lv_style_set_border_width(&btnSEL,3);
		lv_style_set_radius(&btnSEL,1);

		
		//start auton button
		startAuton = lv_btn_create(lv_scr_act());
		lv_obj_add_style(startAuton,&btnREL,0);
		lv_obj_add_style(startAuton,&btnREL,LV_STATE_PRESSED);
		lv_obj_set_size(startAuton,200,30);
		lv_obj_set_pos(startAuton,280,205); 
		lv_obj_t * startAutonLabel = lv_label_create(startAuton);
		lv_label_set_text(startAutonLabel, "Start Autonomous");
		lv_obj_center(startAutonLabel);
		lv_obj_add_event_cb(startAuton,startAutonomous,LV_EVENT_CLICKED,NULL);

		loadAllianceSelect();
		loadTypeSelect();
		
	}
	void auton(){
		lv_obj_clean(lv_scr_act());
	}
	void debugLoop(pros::Controller Controller1){
		if(!autonStarted){
			while(!autonStarted && !Controller1.get_digital(DIGITAL_A) && !Controller1.get_digital(DIGITAL_B)){
				pros::delay(100);
			}
			clearScreen();
			if(!(Controller1.get_digital(DIGITAL_A) || pros::c::competition_is_connected())){
				pros::delay(3000);
				autonomous();
				pros::delay(5000);
				opcontrol();
			}
			
		}else{
			clearScreen();
		}
	}
}
