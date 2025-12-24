/*
	Author: Antoine FAURE.
	Licence of this file: free for educational, commercial or other usage.
	Last update: 2025 - 12 (december) - 21

	Content of file: the parts of a military hovercraft model
	Note: Everything in this file as been prefixed with 'HoverCraft_' in order 
		to avoid names collisions as much as possible.
	
	The x axis is the width and the z axis is the length of the hovercraft. The z axis goes from 
		the center to the pilot box, so the -z axis points to the rear fans. 
	
	Usage: use the object statement like this: 
		object{ HoverCraft_Object }
	
	Or you can use the macro:
	HoverCraft_PlaceObject(AreFansTurning, Frame, FramesNumber, IsThereDirtOnFloater, Transform)
		- With 'AreFansTurning' a boolean wether you want the two rear fans rotate or 
			not ( 'true' or 'false' value to supply ).
		- 'Frame' and FramesNumber are here for the animation of the rear fans.
		- 'IsThereDirtOnFloater' a boolean to append some dirt on the 50 % top part of the floater.
		- And 'Transform' to apply a serie of transformations to the hovercraft, for example: 
			transform{ scale 0.25 rotate 75 * y translate < -4, 0, 12 > }
			transform{ scale 4 rotate 45 * y translate 14 * z }
	
	You can use these sets of macro to display informations in the the console (see the far end of this file):
		HoverCraft_DisplaySize()
		HoverCraft_DisplayBoundaries()
		HoverCraft_DisplayCenterCoordinates()
*/

#declare HoverCraft_Length = 21;
#declare HoverCraft_Width = 12;
#declare HoverCraft_FloaterRadius = 1;
#declare HoverCraft_FloaterCornerBigRadius = 2;
#declare HoverCraft_FloaterCornerHorizontalSize = HoverCraft_FloaterRadius + HoverCraft_FloaterCornerBigRadius * 2;
#declare HoverCraft_FloorHighness = HoverCraft_FloaterRadius / 10;

#declare HoverCraft_FanRoundRadius = 1.8;
#declare HoverCraft_FanRoundBorder = 0.1;
#declare HoverCraft_FanDepth = 1.8;
#declare HoverCraft_FanStalkRadius = 0.25;
#declare HoverCraft_FanShutterThickness = 0.035; 
#declare HoverCraft_FanRoundAccuracy = 180;
#declare HoverCraft_FanBladeNumber = 4;
#declare HoverCraft_FanAngle = 360 / HoverCraft_FanBladeNumber * 0.85;
#declare HoverCraft_StructWidthPercent = 0.75;
#declare HoverCraft_StructSlopeLength = HoverCraft_Length / 7;

#declare HoverCraft_MiddleWindowBorderScale = 0.85;

#declare HoverCraft_PilotBoxZStart = HoverCraft_Length / 4;
#declare HoverCraft_PilotBoxLength = HoverCraft_Length / 6;
#declare HoverCraft_PilotBoxWidth = HoverCraft_Width / 3.5;
#declare HoverCraft_PilotBoxHeightPercent = 1.25;
#declare HoverCraft_PilotBoxArmoured = 0.05;
#declare HoverCraft_PilotBoxWindowHeightPercent = 0.4;

#declare HoverCraft_AccessPlatformStalkRadius = 0.075;
#declare HoverCraft_AccessPlatformStalkHighness = 3;
#declare HoverCraft_AccessPlatformFinalScale = 0.35;

#declare HoverCraft_FloaterColor = color srgb 0.25;
#declare HoverCraft_FloaterTexture = texture{ pigment{ HoverCraft_FloaterColor } finish{ specular 0.015 roughness 0.001 phong 0 phong_size 0 } }

#declare HoverCraft_DirtRatio = 1.4;
#declare HoverCraft_DirtColor1 = color srgb < 90 / 255 * HoverCraft_DirtRatio, 90 / 255 * HoverCraft_DirtRatio, 86 / 255 * HoverCraft_DirtRatio >;
#declare HoverCraft_DirtColor2 = color srgb < 90 / 255 * HoverCraft_DirtRatio, 90 / 255 * HoverCraft_DirtRatio, 86 / 255 * HoverCraft_DirtRatio > 
											+ < 0.05, 0.05, 0.05 > transmit 0.15;
#declare HoverCraft_ClearColor = color HoverCraft_DirtColor1 transmit 1;

#declare HoverCraft_DirtMixPigment = pigment{ bozo color_map{ 
															[ 0.2 HoverCraft_ClearColor ]
															[ 0.2 HoverCraft_DirtColor1 ]
															[ 0.5 HoverCraft_DirtColor1 ]
															[ 0.5 HoverCraft_DirtColor2 ]
															[ 0.8 HoverCraft_DirtColor2 ]
															[ 0.8 HoverCraft_ClearColor ]
														}
											scale 0.025
											scale 1 / < 1, HoverCraft_FloaterRadius * 2, 1 >
										}
				
#declare HoverCraft_FloaterZDirtPigment = pigment{ gradient z pigment_map{
												[ 0 HoverCraft_DirtMixPigment ]
												[ 0.175 HoverCraft_DirtMixPigment ]
												[ 0.2333 HoverCraft_ClearColor ]
												}
												rotate 180 * y
												scale HoverCraft_Length * 1.1
												translate HoverCraft_Length / 2 * z
											}						
#declare HoverCraft_FloaterYDirtPigment = pigment{ gradient y pigment_map{
												[ 0 HoverCraft_ClearColor ]
												[ 0.401 HoverCraft_ClearColor ]
												[ 0.62 HoverCraft_FloaterZDirtPigment ]
												[ 1 HoverCraft_FloaterZDirtPigment ]
																	}
													scale < 1, HoverCraft_FloaterRadius * 2, 1 >
													warp{ turbulence < 0, 0.1, 0.5 > }
												}



#declare HoverCraft_MetalColor1 = color srgb < 184 / 255, 168 / 255, 144 / 255 >;
#declare HoverCraft_MetalColor2 = color srgb < 142 / 255, 130 / 255, 93 / 255 >;
#declare HoverCraft_MetalColor3 = color srgb < 111 / 255, 101 / 255, 79 / 255 >;
#declare HoverCraft_MetalFinish = finish{ roughness 0.001 specular 0.005 phong 0 phong_size 0 }
#declare HoverCraft_MilitaryTexture = texture{ pigment{ gradient z color_map{ 
												[ 0 HoverCraft_MetalColor1 ]
												[ 0.3 HoverCraft_MetalColor1 ]
												[ 0.3 HoverCraft_MetalColor2 ]
												[ 0.6 HoverCraft_MetalColor2 ]
												[ 0.6 HoverCraft_MetalColor3 ]
												[ 1 HoverCraft_MetalColor3 ]
															}
													scale < 1, 1, 4 >
													warp{ turbulence < 0, 0.1, 1 > octaves 1 lambda 1 }
												} 
												finish{ HoverCraft_MetalFinish }
										}

#declare HoverCraft_FanBladeColor = color srgb 0.65;
#declare HoverCraft_FanBladeTexture = texture{ pigment{ HoverCraft_FanBladeColor } finish{ specular 0.3 roughness 0.01 } }
#declare HoverCraft_TurningFanBladesTexture = texture{ pigment{ HoverCraft_FanBladeColor transmit 0.25	} finish{ specular 0.3 roughness 0.01 } }

#declare HoverCraft_PilotBoxFacilityTexture = texture{ pigment{ HoverCraft_MetalColor1 } finish{ HoverCraft_MetalFinish } }

#declare HoverCraft_GlassColor = color srgb < 23 / 255, 119 / 255, 157 / 255 > transmit 0.6;
#declare HoverCraft_GlassTexture = texture{ pigment{ HoverCraft_GlassColor } finish{ specular 0.2 roughness 0.01 } }

#declare HoverCraft_WindowsBorderTexture = texture{ pigment{ color srgb 0.65 } finish{ specular 0.2 roughness 0.01 } }
#declare HoverCraft_MiddleWindowsGlassColor = color srgb < 23 / 255, 119 / 255, 157 / 255 > transmit 0.45;
#declare HoverCraft_MiddleWindowsGlassTexture= texture{ pigment{ color srgb < 103 / 255, 149 / 255, 157 / 255 > transmit 0.5 } 
															finish{ specular 0.001 roughness 0.001 } 
												}

#declare HoverCraft_AccessPlatformColor = color srgb < 154 / 255, 141 / 255, 127 / 255 >;

#declare HoverCraft_BatteryTexture = texture{ pigment{ color srgb 0.8 } finish{ HoverCraft_MetalFinish } }

#declare HoverCraft_FloaterCornerGeom = 
difference{
	torus{ HoverCraft_FloaterCornerBigRadius, HoverCraft_FloaterRadius }
	box{ < -HoverCraft_FloaterCornerHorizontalSize, -HoverCraft_FloaterRadius * 1.1, 0 >,
		< HoverCraft_FloaterCornerHorizontalSize, HoverCraft_FloaterRadius * 1.1, -HoverCraft_FloaterCornerBigRadius * 2 > } // -z box
	box{ < 0, -HoverCraft_FloaterRadius * 1.1, -HoverCraft_FloaterCornerHorizontalSize >,
		< HoverCraft_FloaterCornerBigRadius * 2, HoverCraft_FloaterRadius * 1.1, HoverCraft_FloaterCornerHorizontalSize > } // +x box
}

#declare HoverCraft_FloaterCornersPos = 
array[4]{ < -HoverCraft_Width / 2 + HoverCraft_FloaterRadius + HoverCraft_FloaterCornerBigRadius, HoverCraft_FloaterRadius, 
			HoverCraft_Length / 2 - HoverCraft_FloaterRadius - HoverCraft_FloaterCornerBigRadius >,
		< HoverCraft_Width / 2 - HoverCraft_FloaterRadius - HoverCraft_FloaterCornerBigRadius, HoverCraft_FloaterRadius, 
			HoverCraft_Length / 2 - HoverCraft_FloaterRadius - HoverCraft_FloaterCornerBigRadius >,
		< HoverCraft_Width / 2 - HoverCraft_FloaterRadius - HoverCraft_FloaterCornerBigRadius, HoverCraft_FloaterRadius, 
			-HoverCraft_Length / 2 + HoverCraft_FloaterRadius + HoverCraft_FloaterCornerBigRadius >,
		< -HoverCraft_Width / 2 + HoverCraft_FloaterRadius + HoverCraft_FloaterCornerBigRadius, HoverCraft_FloaterRadius, 
			-HoverCraft_Length / 2 + HoverCraft_FloaterRadius + HoverCraft_FloaterCornerBigRadius > }

#declare HoverCraft_FloaterGeom =
union{
	object{ HoverCraft_FloaterCornerGeom translate HoverCraft_FloaterCornersPos[0] } //-x +z pos
	object{ HoverCraft_FloaterCornerGeom rotate 90 * y translate HoverCraft_FloaterCornersPos[1] } //+x +z pos
	object{ HoverCraft_FloaterCornerGeom rotate 180 * y translate HoverCraft_FloaterCornersPos[2] } //+x -z pos
	object{ HoverCraft_FloaterCornerGeom rotate -90 * y translate HoverCraft_FloaterCornersPos[3] } //-x -z pos
	cylinder{ HoverCraft_FloaterCornersPos[0], HoverCraft_FloaterCornersPos[1], HoverCraft_FloaterRadius translate HoverCraft_FloaterCornerBigRadius * z }
	cylinder{ HoverCraft_FloaterCornersPos[1], HoverCraft_FloaterCornersPos[2], HoverCraft_FloaterRadius translate HoverCraft_FloaterCornerBigRadius * x }
	cylinder{ HoverCraft_FloaterCornersPos[0], HoverCraft_FloaterCornersPos[3], HoverCraft_FloaterRadius translate -HoverCraft_FloaterCornerBigRadius * x }
	cylinder{ HoverCraft_FloaterCornersPos[2], HoverCraft_FloaterCornersPos[3], HoverCraft_FloaterRadius translate -HoverCraft_FloaterCornerBigRadius * z }
	texture{ HoverCraft_FloaterTexture }
}

#declare HoverCraft_Floor =
union{
	cylinder{ HoverCraft_FloaterCornersPos[0], HoverCraft_FloaterCornersPos[0] + < 0, HoverCraft_FloorHighness, 0 >, HoverCraft_FloaterCornerBigRadius }
	cylinder{ HoverCraft_FloaterCornersPos[1], HoverCraft_FloaterCornersPos[1] + < 0, HoverCraft_FloorHighness, 0 >, HoverCraft_FloaterCornerBigRadius }
	cylinder{ HoverCraft_FloaterCornersPos[2], HoverCraft_FloaterCornersPos[2] + < 0, HoverCraft_FloorHighness, 0 >, HoverCraft_FloaterCornerBigRadius }
	cylinder{ HoverCraft_FloaterCornersPos[3], HoverCraft_FloaterCornersPos[3] + < 0, HoverCraft_FloorHighness, 0 >, HoverCraft_FloaterCornerBigRadius }
	box{ HoverCraft_FloaterCornersPos[0] + < 0, HoverCraft_FloorHighness, HoverCraft_FloaterCornerBigRadius >, 
			HoverCraft_FloaterCornersPos[2] + < 0, 0, -HoverCraft_FloaterCornerBigRadius > }//+z -z floor
	box{ HoverCraft_FloaterCornersPos[0] + < -HoverCraft_FloaterCornerBigRadius, HoverCraft_FloorHighness, 0 > , 
			HoverCraft_FloaterCornersPos[2] + < HoverCraft_FloaterCornerBigRadius, 0, 0 > }//+x -x floor
	translate HoverCraft_FloaterRadius * y
}

#declare HoverCraft_FanShutter =
box{ < -HoverCraft_FanShutterThickness / 2, -HoverCraft_FanRoundRadius, 0 >, 
		< HoverCraft_FanShutterThickness / 2, HoverCraft_FanRoundRadius, -HoverCraft_FanDepth / 2 > 
	translate < 0, 0, -HoverCraft_FanDepth - HoverCraft_FanRoundBorder >
}

#declare HoverCraft_FanGeomPosition =
< 0, max_extent( HoverCraft_Floor ).y + HoverCraft_FanRoundRadius * 1.2, min_extent( HoverCraft_Floor ).z + HoverCraft_FanDepth * 1.2 >;

#declare HoverCraft_FanGeom =
union{
	torus{ HoverCraft_FanRoundRadius - HoverCraft_FanRoundBorder, HoverCraft_FanRoundBorder rotate 90 * x }
	torus{ HoverCraft_FanRoundRadius - HoverCraft_FanRoundBorder, HoverCraft_FanRoundBorder rotate 90 * x translate -HoverCraft_FanDepth * z }
	difference{
		cylinder{ < 0, 0, 0 >, < 0, 0, -HoverCraft_FanDepth >, HoverCraft_FanRoundRadius }
		cylinder{ < 0, 0, 1 >, < 0, 0, -HoverCraft_FanDepth * 2 >, HoverCraft_FanRoundRadius - HoverCraft_FanRoundBorder * 2 }
	}
	sphere_sweep{ linear_spline 3, 
		< 0, 0, HoverCraft_FanDepth / 8 >, HoverCraft_FanStalkRadius,
		< 0, 0, HoverCraft_FanDepth >, HoverCraft_FanStalkRadius,
		< 0, -HoverCraft_FanRoundRadius * 1.2, HoverCraft_FanDepth * 1.5 >, HoverCraft_FanStalkRadius
	}
	object{ HoverCraft_FanShutter }
	object{ HoverCraft_FanShutter translate -HoverCraft_FanRoundRadius / 2 * x }
	object{ HoverCraft_FanShutter translate HoverCraft_FanRoundRadius / 2 * x }
	translate HoverCraft_FanGeomPosition
}

#declare HoverCraft_FanSample =
mesh{
	#local HoverCraft_FanFinalRadius = HoverCraft_FanRoundRadius - HoverCraft_FanRoundBorder;
	#for( FanAngle, 0, HoverCraft_FanRoundAccuracy * 0.65 )
		#local HoverCraft_FanDepthPercent = 0.8;
		#local HoverCraft_FanTrianglePointZ_CoordA = -HoverCraft_FanDepth * HoverCraft_FanDepthPercent / HoverCraft_FanRoundAccuracy * FanAngle;
		#local HoverCraft_FanTrianglePointZ_CoordB = -HoverCraft_FanDepth * HoverCraft_FanDepthPercent / HoverCraft_FanRoundAccuracy * ( FanAngle + 1 );
		#local HoverCraft_FanTrianglePointZ_RotateValueA = 360 / HoverCraft_FanBladeNumber / HoverCraft_FanRoundAccuracy * FanAngle;
		#local HoverCraft_FanTrianglePointZ_RotateValueB = 360 / HoverCraft_FanBladeNumber / HoverCraft_FanRoundAccuracy * ( FanAngle + 1 );
		
		triangle{ 
			< 0, 0, 0 >, 
			vrotate( < 0, HoverCraft_FanFinalRadius, HoverCraft_FanTrianglePointZ_CoordA >, < 0, 0, HoverCraft_FanTrianglePointZ_RotateValueA > )
			vrotate( < 0, HoverCraft_FanFinalRadius, HoverCraft_FanTrianglePointZ_CoordB >, < 0, 0, HoverCraft_FanTrianglePointZ_RotateValueB > )
		}
	#end
}

#macro HoverCraft_PlaceRoundFans(AreFansTurning, Frame, FramesNumber, CustomPosition)
	union{
		#for( It, 0, HoverCraft_FanBladeNumber - 1 )
			object{ HoverCraft_FanSample rotate 360 / HoverCraft_FanBladeNumber * It * z 
				#if( AreFansTurning )
					texture{ HoverCraft_TurningFanBladesTexture } 
				#else
					texture{ HoverCraft_FanBladeTexture }
				#end
			}
		#end
		rotate 360 / HoverCraft_FanBladeNumber / FramesNumber * Frame * z
		translate HoverCraft_FanGeomPosition + CustomPosition
	}
#end

#declare HoverCraft_BoxUnderTheFans =
box{ < min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent, 
		min_extent( HoverCraft_Floor ).y - 0.001, 
		HoverCraft_FanDepth * 1.5 + min_extent( HoverCraft_Floor ).z >, 
	< max_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent, 
		max_extent( HoverCraft_FanGeom ).y - HoverCraft_FanRoundRadius * 2, 
		min_extent( HoverCraft_Floor ).z > 
}

#declare HoverCraft_StructRearSlope =
prism{ linear_sweep linear_spline -min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent, -max_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent, 5,
	< 0, 0 >, 
	< 0, -HoverCraft_StructSlopeLength >, 
	< max_extent( HoverCraft_BoxUnderTheFans ).y - min_extent( HoverCraft_BoxUnderTheFans ).y, -HoverCraft_StructSlopeLength >,
	< ( max_extent( HoverCraft_BoxUnderTheFans ).y - min_extent( HoverCraft_BoxUnderTheFans ).y ) * 4, 0 >,
	< 0, 0 >
	rotate 90 * z
	translate < 0, min_extent( HoverCraft_Floor ).y - 0.001, HoverCraft_FanDepth * 1.5 + min_extent( HoverCraft_Floor ).z + HoverCraft_StructSlopeLength >
}

#declare HoverCraft_CenterBlockYTop = min_extent( HoverCraft_Floor ).y - 0.001 + ( max_extent( HoverCraft_BoxUnderTheFans ).y 
										- min_extent( HoverCraft_BoxUnderTheFans ).y ) * 4;
#declare HoverCraft_CenterBlockZMin = HoverCraft_FanDepth * 1.5 + min_extent( HoverCraft_Floor ).z + HoverCraft_StructSlopeLength;
#declare HoverCraft_CenterBlockHighness = HoverCraft_CenterBlockYTop - min_extent( HoverCraft_Floor ).y;

#declare HoverCraft_SideWindowWidth = 0.25;
#declare HoverCraft_SideWindowDiffDepth = 0.75;
#declare HoverCraft_SideWindowCornerPercent = 0.65;
#declare HoverCraft_SideWindowHeight = 1;
#declare HoverCraft_WindowScale = < 0.98, 1, 0.98 >;

#declare HoverCraft_PrismWindow =
prism{ linear_sweep linear_spline 0, HoverCraft_SideWindowHeight, 9, 
		< -HoverCraft_SideWindowWidth, 0.3 >,
		< -HoverCraft_SideWindowWidth * HoverCraft_SideWindowCornerPercent, 0.4 >,
		< HoverCraft_SideWindowWidth * HoverCraft_SideWindowCornerPercent, 0.4 >,
		< HoverCraft_SideWindowWidth, 0.3 >,
		< HoverCraft_SideWindowWidth, -0.3 >,
		< HoverCraft_SideWindowWidth * HoverCraft_SideWindowCornerPercent, -0.4 >,
		< -HoverCraft_SideWindowWidth * HoverCraft_SideWindowCornerPercent, -0.4 >,
		< -HoverCraft_SideWindowWidth, -0.3 >,
		< -HoverCraft_SideWindowWidth, 0.3 >
		rotate -90 * y
}

#declare HoverCraft_PrismWindowDiff =
object{ HoverCraft_PrismWindow }

#declare HoverCraft_FinalCenterWindow =
union{
	difference{
		object{ HoverCraft_PrismWindow scale 1.025}
		object{ HoverCraft_PrismWindow scale < HoverCraft_MiddleWindowBorderScale, 1.2, HoverCraft_MiddleWindowBorderScale > }
		texture{ HoverCraft_WindowsBorderTexture }
	}
	object{ HoverCraft_PrismWindow scale < HoverCraft_MiddleWindowBorderScale, 1.025, HoverCraft_MiddleWindowBorderScale > 
		texture{ HoverCraft_MiddleWindowsGlassTexture } 
	}
}


#declare HoverCraft_CenterBlockFirstBlock = box{ < -min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent,
													min_extent( HoverCraft_Floor ).y - 0.001, 
													HoverCraft_CenterBlockZMin >,
												< -max_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent, 
													min_extent( HoverCraft_Floor ).y + HoverCraft_CenterBlockHighness * 0.25,
													HoverCraft_PilotBoxZStart > 
											}
											
#declare HoverCraft_CenterBlockSecondBlock = box{< -min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent * 0.96, 
													min_extent( HoverCraft_Floor ).y + HoverCraft_CenterBlockHighness * 0.25, 
													HoverCraft_CenterBlockZMin >,
												< -max_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent * 0.96, 
													min_extent( HoverCraft_Floor ).y + HoverCraft_CenterBlockHighness * 0.75, 
													HoverCraft_PilotBoxZStart > }	

#declare HoverCraft_CenterBlockThirdBlock = box{< -min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent * 0.92, 
													min_extent( HoverCraft_Floor ).y + HoverCraft_CenterBlockHighness * 0.75, 
													HoverCraft_CenterBlockZMin >,
												< -max_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent * 0.92, 
													HoverCraft_CenterBlockYTop, 
													HoverCraft_PilotBoxZStart > }


#declare HoverCraft_CenterBlock =
difference{
		union{
			object{ HoverCraft_CenterBlockFirstBlock }
			object{ HoverCraft_CenterBlockSecondBlock }
			object{ HoverCraft_CenterBlockThirdBlock }
		}
		#local HoverCraft_WindowY_Center = ( max_extent( HoverCraft_CenterBlockSecondBlock ).y + min_extent( HoverCraft_CenterBlockSecondBlock ).y ) / 2;
		#local HoverCraft_WindowZ_Center = ( max_extent( HoverCraft_CenterBlockSecondBlock ).z + min_extent( HoverCraft_CenterBlockSecondBlock ).z ) / 2;
		#local HoverCraft_SecondCenterBlockSize = max_extent( HoverCraft_CenterBlockSecondBlock ) - min_extent( HoverCraft_CenterBlockSecondBlock );
	
		object{ HoverCraft_PrismWindowDiff rotate 90 * z 
			translate < min_extent( HoverCraft_CenterBlockSecondBlock ).x + HoverCraft_SideWindowDiffDepth, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center + HoverCraft_SecondCenterBlockSize.z / 4 > }
					
		object{ HoverCraft_PrismWindowDiff rotate 90 * z 
			translate < min_extent( HoverCraft_CenterBlockSecondBlock ).x + HoverCraft_SideWindowDiffDepth, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center > }
					
		object{ HoverCraft_PrismWindowDiff rotate 90 * z 
			translate < min_extent( HoverCraft_CenterBlockSecondBlock ).x + HoverCraft_SideWindowDiffDepth, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center - HoverCraft_SecondCenterBlockSize.z / 4 > }
					
	
		object{ HoverCraft_PrismWindowDiff rotate -90 * z 
			translate < max_extent( HoverCraft_CenterBlockSecondBlock ).x - HoverCraft_SideWindowDiffDepth, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center + HoverCraft_SecondCenterBlockSize.z / 4 > }
					
		object{ HoverCraft_PrismWindowDiff rotate -90 * z 
			translate < max_extent( HoverCraft_CenterBlockSecondBlock ).x - HoverCraft_SideWindowDiffDepth, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center > }
					
		object{ HoverCraft_PrismWindowDiff rotate -90 * z 
			translate < max_extent( HoverCraft_CenterBlockSecondBlock ).x - HoverCraft_SideWindowDiffDepth, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center - HoverCraft_SecondCenterBlockSize.z / 4 > }
}

#declare HoverCraft_CenterBlockSideWindows =
union{
	object{ HoverCraft_FinalCenterWindow scale HoverCraft_WindowScale rotate 90 * z
		translate < min_extent( HoverCraft_CenterBlockSecondBlock ).x + HoverCraft_SideWindowHeight, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center + HoverCraft_SecondCenterBlockSize.z / 4 > 
	}
	object{ HoverCraft_FinalCenterWindow scale HoverCraft_WindowScale rotate 90 * z
		translate < min_extent( HoverCraft_CenterBlockSecondBlock ).x + HoverCraft_SideWindowHeight, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center > 
	}
	object{ HoverCraft_FinalCenterWindow scale HoverCraft_WindowScale rotate 90 * z
		translate < min_extent( HoverCraft_CenterBlockSecondBlock ).x + HoverCraft_SideWindowHeight, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center - HoverCraft_SecondCenterBlockSize.z / 4 > 
	}
	
	object{ HoverCraft_FinalCenterWindow scale HoverCraft_WindowScale rotate -90 * z
		translate < max_extent( HoverCraft_CenterBlockSecondBlock ).x - HoverCraft_SideWindowHeight, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center + HoverCraft_SecondCenterBlockSize.z / 4 > 
	}
	object{ HoverCraft_FinalCenterWindow scale HoverCraft_WindowScale rotate -90 * z
		translate < max_extent( HoverCraft_CenterBlockSecondBlock ).x - HoverCraft_SideWindowHeight, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center > 
	}
	object{ HoverCraft_FinalCenterWindow scale HoverCraft_WindowScale rotate -90 * z
		translate < max_extent( HoverCraft_CenterBlockSecondBlock ).x - HoverCraft_SideWindowHeight, HoverCraft_WindowY_Center, HoverCraft_WindowZ_Center - HoverCraft_SecondCenterBlockSize.z / 4 > 
	}
}

#declare HoverCraft_CenterBlockSize = max_extent( HoverCraft_CenterBlock ) - min_extent( HoverCraft_CenterBlock );
#declare HoverCraft_PilotBoxTopZCoord = HoverCraft_PilotBoxLength * 3 / 4;

#declare HoverCraft_CenterBlockPlaqueWidth = HoverCraft_CenterBlockSize.x * 0.8;
#declare HoverCraft_CenterBlockPlaqueThickness = HoverCraft_CenterBlockSize.y * 0.075;

#declare HoverCraft_CenterBlockPlaque =
box{ < -HoverCraft_CenterBlockPlaqueWidth / 2, max_extent(HoverCraft_CenterBlock).y, min_extent(HoverCraft_CenterBlock).z >,
		< HoverCraft_CenterBlockPlaqueWidth / 2, max_extent(HoverCraft_CenterBlock).y + HoverCraft_CenterBlockPlaqueThickness, max_extent(HoverCraft_CenterBlock).z > 
}

#declare HoverCraft_CenterBlockLines =
prism{ linear_sweep linear_spline 
	-HoverCraft_CenterBlockPlaqueWidth / 2, HoverCraft_CenterBlockPlaqueWidth / 2, 4,
	< 0, HoverCraft_CenterBlockPlaqueThickness / 3 >, < 0, -HoverCraft_CenterBlockPlaqueThickness / 3 >, 
	< HoverCraft_CenterBlockPlaqueThickness / 2, 0 >, < 0, HoverCraft_CenterBlockPlaqueThickness / 3 > 
	rotate 90 * z
}

#macro HoverCraft_PlaceCenterBlockLines(LinesNumber)
	#for( It, 0, LinesNumber - 1 )
		object{ HoverCraft_CenterBlockLines 
			translate < 0, max_extent(HoverCraft_CenterBlockPlaque).y, 
				max_extent(HoverCraft_CenterBlockPlaque).z - max_extent(HoverCraft_CenterBlockPlaque).z * 0.1
				- It * (HoverCraft_CenterBlockSize).z / LinesNumber >
		}
	#end
#end

#declare HoverCraft_PilotBox =
prism{ linear_sweep linear_spline 0, HoverCraft_PilotBoxWidth, 6,
	< 0, 0 >, 
	< HoverCraft_CenterBlockSize.y * HoverCraft_PilotBoxHeightPercent, 0 >, 
	< HoverCraft_CenterBlockSize.y * HoverCraft_PilotBoxHeightPercent, HoverCraft_PilotBoxTopZCoord >,
	< HoverCraft_CenterBlockSize.y * 0.2, HoverCraft_PilotBoxLength >,
	< 0, HoverCraft_PilotBoxLength >,
	< 0, 0 >
	rotate 90 * z
}

#declare HoverCraft_PilotBoxWindowYTop = max_extent( HoverCraft_PilotBox ).y - HoverCraft_PilotBoxArmoured;
#declare HoverCraft_PilotBoxWindowYBottom = max_extent( HoverCraft_PilotBox ).y * ( 1 - HoverCraft_PilotBoxWindowHeightPercent ) 
											- HoverCraft_PilotBoxArmoured;

#declare HoverCraft_PilotBoxFrontSlopeBend = HoverCraft_PilotBoxLength - HoverCraft_PilotBoxTopZCoord;
#declare HoverCraft_PilotBoxSlopeHighness = HoverCraft_CenterBlockSize.y * HoverCraft_PilotBoxHeightPercent - HoverCraft_CenterBlockSize.y * 0.2;
#declare HoverCraft_PilotBoxMiddleWindowFront = HoverCraft_PilotBoxFrontSlopeBend * ( HoverCraft_PilotBoxWindowYTop - HoverCraft_PilotBoxWindowYBottom ) / HoverCraft_PilotBoxSlopeHighness;

#declare HoverCraft_PilotBoxMiddleWindow =
prism{ linear_sweep linear_spline -1, HoverCraft_PilotBoxWidth + 1, 5,
	< 0, 0 >, 
	< HoverCraft_PilotBoxWindowYTop - HoverCraft_PilotBoxWindowYBottom, 0 >,
	< HoverCraft_PilotBoxWindowYTop - HoverCraft_PilotBoxWindowYBottom, 
		HoverCraft_PilotBoxLength * 3 / 4 - HoverCraft_PilotBoxLength * 0.25 - HoverCraft_PilotBoxArmoured * 3 >,
	< 0, HoverCraft_PilotBoxLength * 3 / 4 - HoverCraft_PilotBoxLength * 0.25 - HoverCraft_PilotBoxArmoured * 3 + HoverCraft_PilotBoxMiddleWindowFront >,
	< 0, 0 >
	rotate 90 * z
	translate < 0, HoverCraft_PilotBoxWindowYBottom, HoverCraft_PilotBoxLength * 0.25 + HoverCraft_PilotBoxArmoured >
}

#declare HoverCraft_PilotBoxRearWindow =
box{ < -HoverCraft_PilotBoxWidth * 2, 
		HoverCraft_PilotBoxWindowYTop, 
		HoverCraft_PilotBoxArmoured >,
	< HoverCraft_PilotBoxWidth * 2, 
		HoverCraft_PilotBoxWindowYBottom, 
		HoverCraft_PilotBoxLength * 0.25 > 
}

#declare HoverCraft_PilotBoxFrontWindow =
box{ < -HoverCraft_PilotBoxArmoured, 
		HoverCraft_PilotBoxWindowYTop, 
		HoverCraft_PilotBoxLength * 2 >, 
	< -HoverCraft_PilotBoxWidth + HoverCraft_PilotBoxArmoured,
		HoverCraft_PilotBoxWindowYBottom,
		HoverCraft_PilotBoxArmoured * 2 >
}

#declare HoverCraft_PilotBoxBulk =
difference{
	object{ HoverCraft_PilotBox }
	object{ HoverCraft_PilotBox scale 1 - (HoverCraft_PilotBoxArmoured  * 2) translate -HoverCraft_PilotBoxArmoured / 2 }
}

#declare HoverCraft_PilotBoxGlasses =
union{
	intersection{
		object{ HoverCraft_PilotBoxBulk }
		object{ HoverCraft_PilotBoxFrontWindow }
	}
	intersection{
		object{ HoverCraft_PilotBoxBulk }
		object{ HoverCraft_PilotBoxMiddleWindow }
	}
	intersection{
		object{ HoverCraft_PilotBoxBulk }
		object{ HoverCraft_PilotBoxRearWindow }
	}
	texture{ HoverCraft_GlassTexture }
}

#declare HoverCraft_HollowPilotBox =
union{
	difference{
		object{ HoverCraft_PilotBoxBulk }
		object{ HoverCraft_PilotBoxFrontWindow }
		object{ HoverCraft_PilotBoxMiddleWindow }
		object{ HoverCraft_PilotBoxRearWindow }
	}
	object{ HoverCraft_PilotBoxGlasses }
	translate < min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent + HoverCraft_PilotBoxWidth, 
					min_extent( HoverCraft_Floor ).y - 0.001, 
					HoverCraft_PilotBoxZStart >
}

#declare HoverCraft_HollowPilotBoxSize = max_extent(HoverCraft_HollowPilotBox) - min_extent(HoverCraft_HollowPilotBox);
#declare HoverCraft_PilotBoxCoverObjACenterXPos = min_extent(HoverCraft_HollowPilotBox).x + HoverCraft_HollowPilotBoxSize.x * 0.15;
#declare HoverCraft_PilotBoxCoverObjACenterZPos = min_extent(HoverCraft_HollowPilotBox).z + HoverCraft_HollowPilotBoxSize.z * 0.55;

#declare HoverCraft_PilotBoxCoverObjA = //A flat cylinder as a decoration over the pilot box
union{
	cylinder{ < HoverCraft_PilotBoxCoverObjACenterXPos, max_extent(HoverCraft_HollowPilotBox).y, HoverCraft_PilotBoxCoverObjACenterZPos >, 
				< HoverCraft_PilotBoxCoverObjACenterXPos, max_extent(HoverCraft_HollowPilotBox).y + 0.125, HoverCraft_PilotBoxCoverObjACenterZPos >, 
				HoverCraft_PilotBoxWidth / 14 }
	cylinder{ < HoverCraft_PilotBoxCoverObjACenterXPos, max_extent(HoverCraft_HollowPilotBox).y + 0.125, HoverCraft_PilotBoxCoverObjACenterZPos >,
				< HoverCraft_PilotBoxCoverObjACenterXPos, max_extent(HoverCraft_HollowPilotBox).y + 0.165, HoverCraft_PilotBoxCoverObjACenterZPos >, 
				HoverCraft_PilotBoxWidth / 7.5 }
}

#declare HoverCraft_PilotBoxCoverObjBCenterXPos = min_extent(HoverCraft_HollowPilotBox).x + HoverCraft_HollowPilotBoxSize.x * 0.35;
#declare HoverCraft_PilotBoxCoverObjBCenterZPos = min_extent(HoverCraft_HollowPilotBox).z + HoverCraft_HollowPilotBoxSize.z * 0.2;

#declare HoverCraft_PilotBoxCoverObjB = //A kind of radar as a decoration over the pilot box
union{
	box{ < -HoverCraft_PilotBoxWidth / 2 * 0.18, 0, -HoverCraft_PilotBoxWidth / 2 * 0.17 >, 
			< HoverCraft_PilotBoxWidth / 2 * 0.18, 0.18, HoverCraft_PilotBoxWidth / 2 * 0.21 > }
	box{ < -HoverCraft_PilotBoxWidth / 2 * 0.2, 0.18, -HoverCraft_PilotBoxWidth / 2 * 0.19 >, 
			< HoverCraft_PilotBoxWidth / 2 * 0.2, 0.3, HoverCraft_PilotBoxWidth / 2 * 0.19 > }
	cylinder{ < 0, 0.3, 0 >, < 0, 0.36, 0>, HoverCraft_PilotBoxWidth / 2 * 0.15 }
	box{ < -HoverCraft_PilotBoxWidth / 2 * 0.14, 0.36, -HoverCraft_PilotBoxWidth / 2 * 0.46 >, 
			< HoverCraft_PilotBoxWidth / 2 * 0.14, 0.48, HoverCraft_PilotBoxWidth / 2 * 0.46 > }
	
	translate < HoverCraft_PilotBoxCoverObjBCenterXPos, max_extent(HoverCraft_HollowPilotBox).y, HoverCraft_PilotBoxCoverObjBCenterZPos >
}

#declare HoverCraft_DiveBoardRoundRadius = 0.1;
#declare HoverCraft_DiveBoardWidth = ( HoverCraft_CenterBlockSize.x - HoverCraft_PilotBoxWidth ) / 2;
#declare HoverCraft_DiveBoardDepth = HoverCraft_PilotBoxLength * 0.6825; // 0.7825
#declare HoverCraft_DiveBoard1_Edge = 0.45;
#declare HoverCraft_DiveBoardsYLink = 0.85;

#declare HoverCraft_DiveBoard1 = 
prism{ linear_sweep linear_spline 0, HoverCraft_CenterBlockSize.x - HoverCraft_PilotBoxWidth, 6
	< 0, 0 >,
	< HoverCraft_CenterBlockSize.y, 0 >,
	< HoverCraft_CenterBlockSize.y, HoverCraft_DiveBoardDepth * 0.3 >,
	< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink, HoverCraft_DiveBoardDepth * HoverCraft_DiveBoard1_Edge >,
	< 0, HoverCraft_DiveBoardDepth * HoverCraft_DiveBoard1_Edge >,
	< 0, 0 >
	rotate 90 * z
	translate < min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent + HoverCraft_PilotBoxWidth + HoverCraft_DiveBoardWidth * 2, 
				min_extent( HoverCraft_Floor ).y - 0.001, 
				HoverCraft_PilotBoxZStart >
}

#declare HoverCraft_DiveBoard1_Size = max_extent( HoverCraft_DiveBoard1 ) - min_extent( HoverCraft_DiveBoard1 );

#declare HoverCraft_DiveBoard2_Interstice = 0.025;

#declare HoverCraft_DiveBoard2_DivePlace =
prism{ linear_sweep linear_spline HoverCraft_DiveBoardWidth * 0.1,
										HoverCraft_DiveBoardWidth * 0.4, 
										5,
		< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.94, HoverCraft_DiveBoardDepth * 0.1 >,
		< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.775, HoverCraft_DiveBoardDepth * 0.3 >,
		< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 2, HoverCraft_DiveBoardDepth * 0.3 >,
		< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 2, HoverCraft_DiveBoardDepth * 0.1 >,
		< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.94, HoverCraft_DiveBoardDepth * 0.1 >
		
}

#declare HoverCraft_DiveBoard2_CylinderRadius = 0.05;
#declare HoverCraft_DiveBoard2_ExtremityAngleVector = vrotate( < 0, 0, -HoverCraft_DiveBoard2_CylinderRadius >, < 45, 0, 0 > );

#declare HoverCraft_DiveBoard2_Cylinder =
cylinder{ < 0, HoverCraft_DiveBoard2_Interstice, 0 >, < 0, HoverCraft_DiveBoardWidth - HoverCraft_DiveBoard2_Interstice, 0 >, 
			HoverCraft_DiveBoard2_CylinderRadius }

#declare HoverCraft_DiveBoard2 =
union{
	object{ HoverCraft_DiveBoard2_Cylinder 
		translate < HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.3, 0, HoverCraft_DiveBoardDepth * 1.1 > }
	difference{
		prism{ linear_sweep linear_spline HoverCraft_DiveBoard2_Interstice, 
										HoverCraft_DiveBoardWidth - HoverCraft_DiveBoard2_Interstice, 
										10,
			< 0, 0 >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink, 0 >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.95, HoverCraft_DiveBoardDepth * 0.1 >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.875, HoverCraft_DiveBoardDepth * 0.3 >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.25, HoverCraft_DiveBoardDepth * 0.73 >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.25, HoverCraft_DiveBoardDepth * 0.91 >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.3 + HoverCraft_DiveBoard2_ExtremityAngleVector.y, 
					HoverCraft_DiveBoardDepth * 1.1 + HoverCraft_DiveBoard2_ExtremityAngleVector.z >,
			< HoverCraft_CenterBlockSize.y * HoverCraft_DiveBoardsYLink * 0.3 - HoverCraft_DiveBoard2_ExtremityAngleVector.y, 
					HoverCraft_DiveBoardDepth * 1.1 - HoverCraft_DiveBoard2_ExtremityAngleVector.z >,
			< 0, HoverCraft_DiveBoardDepth >
			< 0, 0 >
		}
		object{ HoverCraft_DiveBoard2_DivePlace }
		object{ HoverCraft_DiveBoard2_DivePlace translate HoverCraft_DiveBoardWidth * 0.5 * y }
	}
	rotate 90 * z						
	translate < min_extent( HoverCraft_Floor ).x * HoverCraft_StructWidthPercent + HoverCraft_PilotBoxWidth + HoverCraft_DiveBoardWidth * 2, 
			min_extent( HoverCraft_Floor ).y - 0.001, 
			HoverCraft_PilotBoxZStart + HoverCraft_DiveBoard1_Size.z >
}

#declare HoverCraft_AccessPlatformBasePtA = < -1, 0, 2 >;
#declare HoverCraft_AccessPlatformBasePtB = < 2, 0, 2 >;
#declare HoverCraft_AccessPlatformBasePtC = < 2, 0, -2 >;
#declare HoverCraft_AccessPlatformBasePtD = < -1, 0, -2 >;

#declare HoverCraft_AccessPlatformBasePtE = HoverCraft_AccessPlatformBasePtA * 0.9 + < 0, 0.8, 0 >;
#declare HoverCraft_AccessPlatformBasePtF = HoverCraft_AccessPlatformBasePtB * < 0.5, 0, 0.9 > + < 0, 0.8, 0 >;
#declare HoverCraft_AccessPlatformBasePtG = HoverCraft_AccessPlatformBasePtC * < 0.5, 0, 0.9 > + < 0, 0.8, 0 >;
#declare HoverCraft_AccessPlatformBasePtH = HoverCraft_AccessPlatformBasePtD * 0.9 + < 0, 0.8, 0 >;

#declare HoverCraft_AccessPlatformBase =
mesh{
	triangle{ HoverCraft_AccessPlatformBasePtA, HoverCraft_AccessPlatformBasePtE, HoverCraft_AccessPlatformBasePtB }
	triangle{ HoverCraft_AccessPlatformBasePtF, HoverCraft_AccessPlatformBasePtE, HoverCraft_AccessPlatformBasePtB }
	triangle{ HoverCraft_AccessPlatformBasePtF, HoverCraft_AccessPlatformBasePtC, HoverCraft_AccessPlatformBasePtB }
	triangle{ HoverCraft_AccessPlatformBasePtF, HoverCraft_AccessPlatformBasePtC, HoverCraft_AccessPlatformBasePtG }
	triangle{ HoverCraft_AccessPlatformBasePtD, HoverCraft_AccessPlatformBasePtH, HoverCraft_AccessPlatformBasePtG }
	triangle{ HoverCraft_AccessPlatformBasePtD, HoverCraft_AccessPlatformBasePtC, HoverCraft_AccessPlatformBasePtG }
	triangle{ HoverCraft_AccessPlatformBasePtD, HoverCraft_AccessPlatformBasePtA, HoverCraft_AccessPlatformBasePtE }
	triangle{ HoverCraft_AccessPlatformBasePtD, HoverCraft_AccessPlatformBasePtH, HoverCraft_AccessPlatformBasePtE }
	triangle{ HoverCraft_AccessPlatformBasePtF, HoverCraft_AccessPlatformBasePtG, HoverCraft_AccessPlatformBasePtE }
	triangle{ HoverCraft_AccessPlatformBasePtG, HoverCraft_AccessPlatformBasePtH, HoverCraft_AccessPlatformBasePtE }
	triangle{ HoverCraft_AccessPlatformBasePtA, HoverCraft_AccessPlatformBasePtB, HoverCraft_AccessPlatformBasePtC }
	triangle{ HoverCraft_AccessPlatformBasePtA, HoverCraft_AccessPlatformBasePtC, HoverCraft_AccessPlatformBasePtD }
	inside_vector < 0, 1, 0 >
}

#declare HoverCraft_AccessPlatformStalkTorusBigRadius = abs( HoverCraft_AccessPlatformBasePtF.z - HoverCraft_AccessPlatformBasePtG.z ) / 20;

#declare HoverCraft_AccessPlatformStalkDiffTorus =
difference{
	torus{ HoverCraft_AccessPlatformStalkTorusBigRadius, HoverCraft_AccessPlatformStalkRadius }
	box{ < -HoverCraft_AccessPlatformStalkTorusBigRadius * 2, -HoverCraft_AccessPlatformStalkTorusBigRadius, 0 >,
		< HoverCraft_AccessPlatformStalkTorusBigRadius * 2, HoverCraft_AccessPlatformStalkTorusBigRadius, -HoverCraft_AccessPlatformStalkTorusBigRadius * 2 > }
	box{ < -HoverCraft_AccessPlatformStalkTorusBigRadius * 2, -HoverCraft_AccessPlatformStalkTorusBigRadius, -HoverCraft_AccessPlatformStalkTorusBigRadius * 2 >,
		< 0, HoverCraft_AccessPlatformStalkTorusBigRadius, HoverCraft_AccessPlatformStalkTorusBigRadius * 2 > }
	rotate 90 * z
}

#declare HoverCraft_AccessPlatformStalk =
union{
	object{ HoverCraft_AccessPlatformStalkDiffTorus 
		translate < 0, HoverCraft_AccessPlatformStalkHighness - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtF.z - 0.1 - HoverCraft_AccessPlatformStalkTorusBigRadius > }
	object{ HoverCraft_AccessPlatformStalkDiffTorus rotate 180 * y 
		translate < 0, HoverCraft_AccessPlatformStalkHighness - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtG.z + 0.1 + HoverCraft_AccessPlatformStalkTorusBigRadius > }
	
	cylinder{ < 0, HoverCraft_AccessPlatformStalkHighness + HoverCraft_AccessPlatformStalkTorusBigRadius - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtF.z - 0.1 - HoverCraft_AccessPlatformStalkTorusBigRadius >, 
		< 0, HoverCraft_AccessPlatformStalkHighness + HoverCraft_AccessPlatformStalkTorusBigRadius - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtG.z + 0.1 + HoverCraft_AccessPlatformStalkTorusBigRadius >, 
		HoverCraft_AccessPlatformStalkRadius }
	
	cylinder{ < 0, 0, HoverCraft_AccessPlatformBasePtF.z - 0.1 >, 
		< 0, HoverCraft_AccessPlatformStalkHighness - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtF.z - 0.1>, 
		HoverCraft_AccessPlatformStalkRadius }
	
	cylinder{ < 0, 0, HoverCraft_AccessPlatformBasePtG.z + 0.1 >, 
		< 0, HoverCraft_AccessPlatformStalkHighness - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtG.z + 0.1 >, 
		HoverCraft_AccessPlatformStalkRadius }
}

#declare HoverCraft_AccessPlatform =
union{
	object{ HoverCraft_AccessPlatformBase }
	cylinder{ < 0, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtF.z - 0.1 >,
			< 0, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtG.z + 0.1 >, 
			0.2 }
	sphere{ < 0, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtF.z - 0.1 >, 0.2 }
	sphere{ < 0, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtG.z + 0.1 >, 0.2 }
	object{ HoverCraft_AccessPlatformStalk }
	
	cylinder{ < HoverCraft_AccessPlatformBasePtF.x, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtF.z - 0.1 >,
			< HoverCraft_AccessPlatformBasePtF.x, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtG.z + 0.1 >, 
			0.1 }
	sphere{ < HoverCraft_AccessPlatformBasePtF.x, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtF.z - 0.1 >, 0.1 }
	sphere{ < HoverCraft_AccessPlatformBasePtF.x, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtG.z + 0.1 >, 0.1 }
	
	cylinder{ < HoverCraft_AccessPlatformBasePtF.x, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtF.z * 0.65 >,
		< 0, HoverCraft_AccessPlatformStalkHighness + HoverCraft_AccessPlatformStalkTorusBigRadius - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtF.z * 0.65 >, 
		HoverCraft_AccessPlatformStalkRadius }
	cylinder{ < HoverCraft_AccessPlatformBasePtF.x, HoverCraft_AccessPlatformBasePtF.y, HoverCraft_AccessPlatformBasePtG.z * 0.65 >,
		< 0, HoverCraft_AccessPlatformStalkHighness + HoverCraft_AccessPlatformStalkTorusBigRadius - HoverCraft_AccessPlatformStalkRadius, HoverCraft_AccessPlatformBasePtG.z * 0.65 >, 
		HoverCraft_AccessPlatformStalkRadius }
	
	scale HoverCraft_AccessPlatformFinalScale
	pigment{ HoverCraft_AccessPlatformColor }
	finish{ HoverCraft_MetalFinish }
}

#declare HoverCraft_Clapet =
superellipsoid{ < 0.25, 0.05 > rotate 90 * x translate y scale < 0.2, 0.05, 0.2 > }

#declare HoverCraft_Sensor =
union{
	cylinder{ < 0, 0, 0 >, < 0, 0.1, 0 >, 0.03 }
	cylinder{ < 0, 0.1, 0 >, < 0, 0.25, 0 >, 0.07 }
}

#declare HoverCraft_BatteryContainer = 
box{< min_extent( HoverCraft_CenterBlock ).x * 0.9, min_extent( HoverCraft_CenterBlock ).y, min_extent( HoverCraft_CenterBlock ).z * 0.9 >, 
	< 	max_extent( HoverCraft_CenterBlock ).x * 0.9, 
		max_extent( HoverCraft_CenterBlock ).y * 4, 
		min_extent( HoverCraft_CenterBlock ).z * 0.75 + ( max_extent( HoverCraft_CenterBlock ).x - min_extent( HoverCraft_CenterBlock ).x ) / 6 > }

#declare HoverCraft_SmallBatteryWidth = ( max_extent( HoverCraft_BatteryContainer ).x - min_extent( HoverCraft_BatteryContainer ).x ) / 22;
#declare HoverCraft_BigBatteryWidth = HoverCraft_SmallBatteryWidth * 4;
#declare HoverCraft_BatteryDepth = max_extent( HoverCraft_BatteryContainer ).z - min_extent( HoverCraft_BatteryContainer ).z;
#declare HoverCraft_BatteryHighness = ( max_extent( HoverCraft_CenterBlock ).y - min_extent( HoverCraft_CenterBlock ).y ) * 1.1;

#declare HoverCraft_BatteryZCenterPosition = ( max_extent( HoverCraft_BatteryContainer ).z + min_extent( HoverCraft_BatteryContainer ).z ) / 2;
#declare HoverCraft_BatteryRound = 0.15;

#declare HoverCraft_SmallBattery = 
superellipsoid{ < HoverCraft_BatteryRound, HoverCraft_BatteryRound > scale 0.5 
				scale < HoverCraft_SmallBatteryWidth, HoverCraft_BatteryHighness, HoverCraft_BatteryDepth > texture{ HoverCraft_BatteryTexture } }
#declare HoverCraft_BigBattery = 
superellipsoid{ < HoverCraft_BatteryRound, HoverCraft_BatteryRound > scale 0.5 
				scale < HoverCraft_BigBatteryWidth, HoverCraft_BatteryHighness, HoverCraft_BatteryDepth > texture{ HoverCraft_BatteryTexture } }

#declare HoverCraft_LedStalksRadius = 0.04;
#declare HoverCraft_LedStalksHighness = ( max_extent( HoverCraft_CenterBlock ).y - min_extent( HoverCraft_CenterBlock ).y ) * 1.5;

#declare HoverCraft_LedStalks =
union{
	cylinder{ < min_extent( HoverCraft_BigBattery ).x, 0, max_extent( HoverCraft_BigBattery ).z >, < 0, HoverCraft_LedStalksHighness, 0 >, HoverCraft_LedStalksRadius }
	cylinder{ < max_extent( HoverCraft_BigBattery ).x, 0, max_extent( HoverCraft_BigBattery ).z >, < 0, HoverCraft_LedStalksHighness, 0 >, HoverCraft_LedStalksRadius }
	cylinder{ < 0, 0, min_extent( HoverCraft_BigBattery ).z >, < 0, HoverCraft_LedStalksHighness, 0 >, HoverCraft_LedStalksRadius }
	texture{ pigment{ HoverCraft_MetalColor1 } finish{ HoverCraft_MetalFinish } }
}

#declare HoverCraft_LedRadius = HoverCraft_LedStalksRadius * 2;

#declare HoverCraft_Led =
union{
	cylinder{ < 0, HoverCraft_LedStalksHighness, 0 >,< 0, HoverCraft_LedStalksHighness + 0.05, 0 >, HoverCraft_LedRadius pigment{ color srgb 0 } }
	cylinder{ < 0, HoverCraft_LedStalksHighness + 0.05, 0 >,< 0, HoverCraft_LedStalksHighness + 0.35, 0 >, HoverCraft_LedRadius 
		texture{ pigment{ color srgb 1 transmit 0.35 } finish{ specular 0.1 roughness 0.01 } }
	}
	cylinder{ < 0, HoverCraft_LedStalksHighness + 0.35, 0 >,< 0, HoverCraft_LedStalksHighness + 0.4, 0 >, HoverCraft_LedRadius pigment{ color srgb 0 } }
}

#declare HoverCraft_RearCenterLedSystem =
union{
	object{ HoverCraft_LedStalks }
	object{ HoverCraft_Led }
}

#declare HoverCraft_AntennaRadius = 0.04;
#declare HoverCraft_AntennaHighness = ( max_extent( HoverCraft_HollowPilotBox ).y - min_extent( HoverCraft_HollowPilotBox ).y ) * 1;

#declare HoverCraft_Antennas =
union{
	cylinder{ < HoverCraft_AntennaRadius, 0, 0 >, < HoverCraft_AntennaRadius, HoverCraft_AntennaHighness * 0.8, 0 >, HoverCraft_AntennaRadius }
	cylinder{ < HoverCraft_AntennaRadius * 4, 0, 0 >, < HoverCraft_AntennaRadius * 4, HoverCraft_AntennaHighness * 1.1, 0 >, HoverCraft_AntennaRadius }
	cylinder{ < HoverCraft_AntennaRadius * 8, 0, 0 >, < HoverCraft_AntennaRadius * 8, HoverCraft_AntennaHighness * 0.95, 0 >, HoverCraft_AntennaRadius }
	texture{ pigment{ color srgb 0.8 } finish{ specular 0.6 roughness 0.2 } }
	
	translate < min_extent( HoverCraft_HollowPilotBox ).x + HoverCraft_AntennaRadius * 4, 
				( max_extent( HoverCraft_HollowPilotBox ).y + min_extent( HoverCraft_HollowPilotBox ).y ) / 2,
				min_extent( HoverCraft_HollowPilotBox ).z + max_extent( HoverCraft_Floor ).z - max_extent( HoverCraft_HollowPilotBox ).z - HoverCraft_AntennaRadius >
}


#declare HoverCraft_SpeakerPyramidTrunk =
prism{ conic_sweep linear_spline 1, 0.4, 5, < -0.5, 1 >, < -0.5, -1 >, < 0.5, -1 >, < 0.5, 1 >, < -0.5, 1 > }

#declare HoverCraft_Speaker =
union{
	difference{
		object{ HoverCraft_SpeakerPyramidTrunk }
		object{ HoverCraft_SpeakerPyramidTrunk translate 0.1 * y }
	}
	box{ < 0.1, 1.0, 0.1 >, < -0.1, 0.41, -0.1 > }
	translate -0.1 * y
	rotate 90 * x
	scale < 0.25, 0.25, 1 >
}

#declare HoverCraft_SpeakerSystem =
union{
	box{< max_extent( HoverCraft_Speaker ).x, max_extent( HoverCraft_Speaker ).y, max_extent( HoverCraft_Speaker ).z >,
		< min_extent( HoverCraft_Speaker ).x, min_extent( HoverCraft_Speaker ).y, min_extent( HoverCraft_Speaker ).z > 
		translate -( max_extent( HoverCraft_Speaker ).z - min_extent( HoverCraft_Speaker ).z ) * z
	}
	object{ HoverCraft_Speaker }
	translate < min_extent( HoverCraft_HollowPilotBox ).x, 
				max_extent( HoverCraft_HollowPilotBox ).y - min_extent( HoverCraft_Speaker ).y, 
				min_extent( HoverCraft_HollowPilotBox ).z + max_extent( HoverCraft_Floor ).z - max_extent( HoverCraft_HollowPilotBox ).z 
					+ ( max_extent( HoverCraft_Speaker ).z - min_extent( HoverCraft_Speaker ).z )
				>
	texture{ pigment{ HoverCraft_MetalColor1 } finish{ HoverCraft_MetalFinish } }
}

#declare HoverCraft_HeadLightRadius = 0.2;

#declare HoverCraft_HeadLight =
difference{
	cylinder{ < 0, 0, 0 >, < 0, 0.45, 0 >, HoverCraft_HeadLightRadius }
	cylinder{ < 0, 0.1, 0 >, < 0, 2, 0 >, HoverCraft_HeadLightRadius * 0.9 }			
}

#declare HoverCraft_HeadLightSystem =
union{
	object{ HoverCraft_HeadLight rotate 100 * x }
	cylinder{ 0, < 0, 0, -0.5 >, HoverCraft_HeadLightRadius / 2 }
	sphere{ < 0, 0, -0.5 >, HoverCraft_HeadLightRadius / 2 }
	cylinder{ < 0, 0, -0.5 >, < 0, -0.5, -0.5 >, HoverCraft_HeadLightRadius / 2 }
		translate < max_extent( HoverCraft_HollowPilotBox ).x - HoverCraft_HeadLightRadius * 2, 
					max_extent( HoverCraft_HollowPilotBox ).y + HoverCraft_HeadLightRadius * 2,
					min_extent( HoverCraft_HollowPilotBox ).z + max_extent( HoverCraft_Floor ).z - max_extent( HoverCraft_HollowPilotBox ).z + 2 >
	
	texture{ pigment{ color srgb 0.5 } finish{ HoverCraft_MetalFinish } }
}

#macro HoverCraft_MakeMainParts(AreFansTurning, Frame, FramesNumber)
	union{
		object{ HoverCraft_Floor }
		object{ HoverCraft_FanGeom translate -HoverCraft_FanRoundRadius * 1.2 * x }
		object{ HoverCraft_FanGeom translate HoverCraft_FanRoundRadius * 1.2 * x }
		HoverCraft_PlaceRoundFans( AreFansTurning, Frame, FramesNumber, < -HoverCraft_FanRoundRadius * 1.2, 0, 0 > )
		HoverCraft_PlaceRoundFans( AreFansTurning, Frame, FramesNumber, < HoverCraft_FanRoundRadius * 1.2, 0, 0 > )
		object{ HoverCraft_BoxUnderTheFans }
		object{ HoverCraft_StructRearSlope }
		
		difference{
			union{
				object{ HoverCraft_CenterBlock }
				object{ HoverCraft_CenterBlockPlaque }
				HoverCraft_PlaceCenterBlockLines(6)//This a macro with the number of lines as parameter
				object{ HoverCraft_CenterBlockSideWindows }
				translate -max_extent( HoverCraft_CenterBlock ).z * z
				#local HoverCraft_CenterBlockZSize = max_extent( HoverCraft_CenterBlock ).z - min_extent( HoverCraft_CenterBlock ).z;
				scale < 1, 1, ( max_extent( HoverCraft_Floor ).z - max_extent( HoverCraft_HollowPilotBox ).z + HoverCraft_CenterBlockZSize ) / HoverCraft_CenterBlockZSize >
				translate ( max_extent( HoverCraft_CenterBlock ).z + ( max_extent( HoverCraft_Floor ).z - max_extent( HoverCraft_HollowPilotBox ).z ) ) * z
			}
			object{ HoverCraft_BatteryContainer }
		}
		union{
			object{ HoverCraft_HollowPilotBox translate -0.02 * x }
			object{ HoverCraft_DiveBoard1 }
			object{ HoverCraft_DiveBoard2 }
			object{ HoverCraft_DiveBoard2 translate -HoverCraft_DiveBoardWidth * x }
			object{ HoverCraft_PilotBoxCoverObjA texture{ HoverCraft_PilotBoxFacilityTexture } }
			object{ HoverCraft_PilotBoxCoverObjB texture{ HoverCraft_PilotBoxFacilityTexture } }
			translate ( max_extent( HoverCraft_Floor ).z - max_extent( HoverCraft_HollowPilotBox ).z ) * z
		}
		object{ HoverCraft_Clapet translate < -HoverCraft_Width * 0.385, max_extent( HoverCraft_Floor ).y, HoverCraft_Length * 0.2 > } 
		object{ HoverCraft_Clapet translate < -HoverCraft_Width * 0.385, max_extent( HoverCraft_Floor ).y, -HoverCraft_Length * 0.25 > } 
		
		object{ HoverCraft_Clapet translate < HoverCraft_Width * 0.385, max_extent( HoverCraft_Floor ).y, HoverCraft_Length * 0.2 > } 
		object{ HoverCraft_Clapet translate < HoverCraft_Width * 0.385, max_extent( HoverCraft_Floor ).y, -HoverCraft_Length * 0.25 > } 
		
		object{ HoverCraft_Sensor translate < -HoverCraft_Width * 0.365, max_extent( HoverCraft_Floor ).y, HoverCraft_Length * 0.275 > }
		
		texture{ HoverCraft_MilitaryTexture }
	}
	object{ HoverCraft_AccessPlatform translate -min_extent( HoverCraft_AccessPlatform ).x * x
		translate < max_extent( HoverCraft_CenterBlock ).x, 
					max_extent( HoverCraft_Floor ).y, min_extent( HoverCraft_CenterBlock ).z > }
	object{ HoverCraft_AccessPlatform translate -min_extent( HoverCraft_AccessPlatform ).x * x rotate 180 * y
		translate < min_extent( HoverCraft_CenterBlock ).x, 
					max_extent( HoverCraft_Floor ).y, min_extent( HoverCraft_CenterBlock ).z > }
	
	object{ HoverCraft_AccessPlatformStalk 
		scale HoverCraft_AccessPlatformFinalScale
		rotate 20 * y
		translate < -HoverCraft_Width * 0.35, max_extent( HoverCraft_Floor ).y, min_extent( HoverCraft_StructRearSlope ).z >
		pigment{ HoverCraft_MetalColor3 }
		finish{ HoverCraft_MetalFinish }
	}
	object{ HoverCraft_AccessPlatformStalk
		scale HoverCraft_AccessPlatformFinalScale
		rotate 160 * y
		translate < HoverCraft_Width * 0.35, max_extent( HoverCraft_Floor ).y, min_extent( HoverCraft_StructRearSlope ).z >
		pigment{ HoverCraft_MetalColor3 }
		finish{ HoverCraft_MetalFinish }
	}
	object{ HoverCraft_SmallBattery 
		translate < max_extent( HoverCraft_BatteryContainer ).x - HoverCraft_SmallBatteryWidth / 2, 
					min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2, 
					HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_SmallBattery 
		translate < min_extent( HoverCraft_BatteryContainer ).x + HoverCraft_SmallBatteryWidth / 2, 
					min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2, 
					HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_BigBattery
		translate < max_extent( HoverCraft_BatteryContainer ).x - HoverCraft_SmallBatteryWidth - HoverCraft_BigBatteryWidth / 2, 
					min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2, 
					HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_BigBattery
		translate < max_extent( HoverCraft_BatteryContainer ).x - HoverCraft_SmallBatteryWidth - HoverCraft_BigBatteryWidth * 3 / 2, 
					min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2, 
					HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_BigBattery
		translate < min_extent( HoverCraft_BatteryContainer ).x + HoverCraft_SmallBatteryWidth + HoverCraft_BigBatteryWidth / 2, 
					min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2, 
					HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_BigBattery
		translate < min_extent( HoverCraft_BatteryContainer ).x + HoverCraft_SmallBatteryWidth + HoverCraft_BigBatteryWidth * 3 / 2, 
					min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2, 
					HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_BigBattery translate < 0, min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2 * 0.9, HoverCraft_BatteryZCenterPosition >	
		texture{ pigment{ HoverCraft_MetalColor3 } finish{ HoverCraft_MetalFinish } }
	}
	object{ HoverCraft_RearCenterLedSystem translate < 0, min_extent( HoverCraft_BatteryContainer ).y + HoverCraft_BatteryHighness / 2 * 0.9, HoverCraft_BatteryZCenterPosition > }
	object{ HoverCraft_Antennas }
	object{ HoverCraft_SpeakerSystem }
	object{ HoverCraft_HeadLightSystem }
#end

#declare HoverCraft_Object =
union{
	object{ HoverCraft_FloaterGeom }
	HoverCraft_MakeMainParts(false, 0, 1)
}

#macro HoverCraft_PlaceObject(AreFansTurning, Frame, FramesNumber, IsThereDirtOnFloater, Transform)
	#if( FramesNumber <= 0 )
		#error "Parse error in 'HoverCraft_PlaceObject()' macro (line 611 of hovercraft.inc file: Frames number was set to 0. Set it to 1 or more."
	#end
	
	union{
		object{ HoverCraft_FloaterGeom 
			#if( IsThereDirtOnFloater )
				texture{ HoverCraft_FloaterTexture }
				texture{ pigment{ HoverCraft_FloaterYDirtPigment } }
			#end
		}
		HoverCraft_MakeMainParts(AreFansTurning, Frame, FramesNumber)
		transform{ Transform }
	}
#end

#declare HoverCraft_Size = max_extent( HoverCraft_Object ) - min_extent( HoverCraft_Object );
#declare HoverCraft_Center = ( max_extent( HoverCraft_Object ) + min_extent( HoverCraft_Object ) ) / 2;

#macro HoverCraft_DisplaySize()
	#debug concat( "Hovercraft size: ", vstr( 3, HoverCraft_Size, ", ", 0, 8 ), "\n" )
#end

#macro HoverCraft_DisplayBoundaries()
	#debug concat( "Hovercraft boundaries: min( ", vstr( 3, min_extent( HoverCraft_Object ), ", ", 0, 4 ), ") max( ", 
				vstr( 3, max_extent( HoverCraft_Object ), ", ", 0, 8), "\n" )
#end

#macro HoverCraft_DisplayCenterCoordinates()
	#debug concat( "Hovercraft center: ", vstr( 3, HoverCraft_Center, ", ", 0, 8 ), "\n" )
#end