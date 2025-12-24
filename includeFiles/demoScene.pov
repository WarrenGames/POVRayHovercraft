#version 3.7;

global_settings{ assumed_gamma 1.0 
	/*
	#default{ finish{ ambient 0 } }
	radiosity{
		pretrace_start 64 / image_width
		pretrace_end 4 / image_width
		count 800
		nearest_count 9
		error_bound 0.5
		low_error_factor 0.5
		media on 
		normal on
	}
	*/
}

background{ color srgb 0 }

#include "hovercraft.inc"
#include "waterScum.inc"

camera{
	location HoverCraft_Size + < 0, 4, 0 >
	look_at HoverCraft_Center
	right image_width / image_height * x
	up y
	sky y
}

light_source{ < 1, 2, 1.5 > * 100 color srgb 1 }

plane{ y, 0 pigment{ checker color srgb < 0, 0.5, 1 > color srgb < 0, 0, 1 > } }

#declare HoverCraft_CustomTransform = transform{ rotate 75 * y }

#declare WaterScumMediaIntensity = 16;

WaterScum_PlaceWholeScumBehindHovercraft(0, 8, transform{ HoverCraft_CustomTransform }, WaterScumMediaIntensity )

HoverCraft_PlaceObject( true, 0, 1, true, HoverCraft_CustomTransform )
