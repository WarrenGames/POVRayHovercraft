/*
	Author: Antoine FAURE.
	Licence of this file: free for educational, commercial or other usage.

	Content of file: the parts of a military hovercraft model
	Note: Everything global in this file as been prefixed with 'WaterScum_' in order 
		to avoid names collisions as much as possible. Some tokens don't have 'WaterScum_'
		as prefix but there are local to a macro.
	
	Usage: 
		Before you use this file you must include the 'hovercraft.inc' file since it depends on the hovercraft 
			traits like its size.
		'WaterScum_PlaceWholeScumBehindHovercraft(Frame, TotalFramesNumber, Hovercraft_Transform, ScumIntensity)'
		with :
			'Frame': the current animation frame if any
			'TotalFramesNumber': the number of frame for an animation
			'Hovercraft_Transform': Since the water scum depends of the hovercraft position you can apply a transform
				to both things (hovercraft and water scum)
			'ScumIntensity': if you are unsure set this value to 16
*/

#declare WaterScum_StartWidth = ( max_extent( HoverCraft_Object ).x - min_extent( HoverCraft_Object ).x ) * 0.55;

#declare WaterScum_EndWidth = WaterScum_StartWidth * 1.4;

#declare WaterScum_Length = HoverCraft_Size.z;

#declare WaterScum_Prism =
prism{ linear_sweep linear_spline 1, 0, 5,
	< -WaterScum_StartWidth / 2, 0 >,
	< WaterScum_StartWidth / 2, 0 >,
	< WaterScum_EndWidth / 2, WaterScum_Length >,
	< -WaterScum_EndWidth / 2, WaterScum_Length >,
	< -WaterScum_StartWidth / 2, 0 >
	rotate 180 * z
	translate 0.5 * y
	rotate 180 * y
	scale < 1, 4, 1 >
}

#declare WaterScum_FadeDensity = 
density{ gradient z density_map{ 
	[ 0 color srgb 0 ]
	[ 0.2 color srgb 0.65 ]
	[ 1 color srgb 1 ] } 
	scale < 1, 1, WaterScum_Length > 
}

#declare WaterScum_PlaneFunc = function{ y - 1 }

#macro WaterScum_PlaceScumCenter(Frame, TotalFramesNumber, WaterScum_CenterTransform, ScumIntensity)
	#local WaterScum_WrinklesFunc = 
		function{ pattern{ wrinkles scale < 0.25, 1, 0.25 >
			warp{ repeat WaterScum_Length * z flip z }
			warp{ turbulence < 1, 0, 1 > lambda 8 }  
			translate -Frame / TotalFramesNumber * WaterScum_Length * z } 
		}
	
	intersection{
		isosurface{
			function{ WaterScum_PlaneFunc(x,y,z) - WaterScum_WrinklesFunc(x,y,z) * 0.2 }
			threshold 0
			accuracy 0.01
			contained_by{ box{ < -WaterScum_EndWidth / 2, 1.05, 0 >,< WaterScum_EndWidth / 2, 1.75, -WaterScum_Length > } } 
			max_gradient 80
			max_trace 2
		}
		object{ WaterScum_Prism }
		hollow no_shadow
		texture{ pigment{ color srgbt 1 } }
		interior{
			media{ emission ScumIntensity intervals 3
				density{ WaterScum_FadeDensity }
			}
		}
		translate -0.75 * y
		transform{ WaterScum_CenterTransform }
		
		
	}
#end

#macro WaterScum_PlaceBorder(Frame, TotalFramesNumber, WaterScum_BorderTransform, ScumIntensity, XDelta)
	
	#local IsoXScale = 1 + ( XDelta + 1 ) / 8;
	#local DiffPrismXScale = 1 + XDelta / 8;
	
	#local WaterScum_WrinklesFunc = 
		function{ pattern{ wrinkles scale < 0.25, 1, 0.25 >
			warp{ repeat WaterScum_Length * z flip z }
			warp{ turbulence < 1, 0, 1 > lambda 8 }  
			translate -Frame / TotalFramesNumber * WaterScum_Length * z } 
		}
	
	difference{
		intersection{
			isosurface{
				function{ WaterScum_PlaneFunc(x,y,z) - WaterScum_WrinklesFunc(x,y,z) * 0.2 }
				threshold 0
				accuracy 0.01
				contained_by{ box{ < -WaterScum_EndWidth / 2 * IsoXScale, 1.05, 0 >,
									< WaterScum_EndWidth / 2 * IsoXScale, 1.75, -WaterScum_Length > } } 
				max_gradient 80
				max_trace 2
			}
			object{ WaterScum_Prism scale < IsoXScale, 1, 1.1 > }
		}
		object{ WaterScum_Prism scale < DiffPrismXScale, 4, 1.2 > }
		hollow no_shadow
		texture{ pigment{ color srgbt 1 } }
		interior{
			media{ emission ScumIntensity intervals 3
				density{ WaterScum_FadeDensity }
			}
		}
		translate -0.75 * y
		transform{ WaterScum_BorderTransform }
	}
#end

#macro WaterScum_Interpolate( X1, X2, Y1, Y2, CurrentX )
	#if( X1 = X2 )
		#error "Can't render, because X1 and X2 have equal values"
	#end
	#local DirCoef = (Y2 - Y1) / ( X2 - X1 );
	#local OriginOffset = Y1 - (DirCoef * X1);

	DirCoef * CurrentX + OriginOffset
#end

#macro WaterScum_PlaceWholeScumBehindHovercraft(Frame, TotalFramesNumber, HoverCraft_Transform, LocalWaterScumIntensity)
	#local WaterScum_TempTransform = transform{ scale < 1, 0.35, 1 > translate < 0, -0.123, -HoverCraft_Size.z / 2 * 0.95 > transform HoverCraft_Transform }
	union{
		WaterScum_PlaceScumCenter( Frame, TotalFramesNumber, WaterScum_TempTransform, LocalWaterScumIntensity )
		#for( It, 0, 3 )
			#local LocalMediaIntensity = WaterScum_Interpolate(0, 4, LocalWaterScumIntensity, 0, It);
			WaterScum_PlaceBorder( Frame, TotalFramesNumber, WaterScum_TempTransform, LocalMediaIntensity, It )
		#end
		no_radiosity
	}
#end