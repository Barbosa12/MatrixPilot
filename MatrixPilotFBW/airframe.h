// This file is part of MatrixPilot.
//
//    http://code.google.com/p/gentlenav/
//
// Copyright 2009-2011 MatrixPilot Team
// See the AUTHORS.TXT file for a list of authors of MatrixPilot.
//
// MatrixPilot is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// MatrixPilot is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with MatrixPilot.  If not, see <http://www.gnu.org/licenses/>.

// Airframe data

#ifndef AIRFRAME_H
#define AIRFRAME_H

#include "airframe_options.h"
#include "minifloat.h"
#include <libq.h>

// Defines unity coefficient of lift as RMAX/2
// This gives headroom for wing sections with Cl above 2.
//#define AFRM_CL_SCALE	(RMAX / 4)
#define AFRM_GRAVITY 	9.81
//#define DEG_TO_CIRCULAR_SCALE (RMAX / 90.0)

#define AFRM_Q16_SCALE	65536.0

/*************************************************************/
// AIRFRAME DATA
// This section describes the airfram data sctructures

typedef struct polar_point_tag
{
	_Q16			alpha;	// Wing angle of attack in degrees
	_Q16 			Cl;		// Lift coefficient
	_Q16			Cd;		// Drag coefficient
	_Q16			Cm;		// 1/4 chord moment coefficient (is it needed with Cp?)
//	fractional		Cp;		// Centre of pressure as percentage of wing chord
//	int		ClCdx10;
} polar_point;


typedef struct polar
{
	int 		airspeed;
	polar_point	points[AFRM_OPT_POINTS_PER_POLAR];
} polar;

extern polar normal_polars[AFRM_OPT_POLARS_PER_CONDITION];


//typedef struct var_polar_tag
//{
//	const unsigned int 			airspeed;		// airspeed for this polar
//	const unsigned int			polar_points;	// Number of polar points
//	const polar_point* const	ppoints;		//
//} var_polar;
//
//
//typedef struct aspd_polar_tag
//{
//	const _Q15				flap_angle;   // 
//	const unsigned int		aspd_polars;  // number of airspeed polars
//	const var_polar** const	ppvar_polar;
//} camber_polars;

// All airspeeds in cm/s
// best lift/drag in ratio * 10
// sink rate in cm/s
typedef struct tag_aero_data
{
	int airspeed_stall;
	int airspeed_vne;
	int airspeed_cruise;
	int cruise_ld;
} aero_data;

typedef struct tag_aero_condition_point
{
	int					condition_point;
	aero_data			data_point;
} aero_condition_point;

extern aero_condition_point camber_aero_data[];
extern int camber_aero_datapoints;


typedef struct control_surface_angle_tag
{
	fractional ap_control;
	_Q16 surface_deflection;
} control_surface_angle;

extern control_surface_angle elevator_angles[];
extern int elevator_angle_points;

extern control_surface_angle rudder_angles[];
extern int rudder_angle_points;

// Decribes delta aileron angles.  Will be replaced by polars
extern control_surface_angle aileron_angles[];
extern int aileron_angle_points;

// Decribes flap angles
extern control_surface_angle flap_angles[];
extern int flap_angle_points;


/*************************************************************/
// AIRFRAME FUNCTIONS
// This section describes functions for calculating aircraft
// aerodynamics and flight surface movements

// Get the required lift coefficient for the airspeed
minifloat afrm_get_required_Cl_mf(int airspeed, minifloat load);

// Get the maximum acceleration avaiable at a given airspeed and Clmax
fractional afrm_get_max_accn_mf(int airspeed, minifloat Clmax);

// Get the required angle of attack (alpha) from a given airspeed and Cl
// Returns RMAX if the required Cl is not acheivable - TODO, not yet!
//minifloat afrm_get_required_alpha(int airspeed, minifloat Cl);
minifloat afrm_get_required_alpha_mf(int airspeed, minifloat Clmf);

// Calculate necessary elevator Cl to balance wing pitch moment
minifloat afrm_get_tail_required_Cl_mf(minifloat wing_aoa);

// Turn tail required Cl into tail pitch against airflow.
minifloat afrm_get_tail_required_alpha(minifloat Clmf_tail);

// Convert elevator aoa into elevator command
fractional lookup_elevator_control( minifloat pitch );

// Find the Cl required from the rudder for the yaw moment
// Yaw moment in Nm
minifloat afrm_get_rudd_required_Cl(int airspeed, minifloat yaw_moment);

// Convert rudder aoa into rudder command
fractional lookup_rudder_control( minifloat aoa );

// Find the aoa delta required to give a required roll rate
minifloat afrm_get_roll_rate_required_aoa_delta(int airspeed, minifloat roll_rate);

// Find the aileron deflection required for the aoa change required
minifloat afrm_get_aileron_deflection(minifloat aoa_delta);

// Lookup the aileron control required for the aileron angle
fractional afrm_lookup_aileron_control( minifloat angle );

int successive_interpolation(int X, int X1, int X2, int Y1, int Y2);
_Q16 successive_interpolation_Q16(_Q16 X, _Q16 X1, _Q16 X2, _Q16 Y1, _Q16 Y2);

extern _Q16 afrm_calc_flap_angle(fractional flap_setting);

extern void afrm_calc_working_wing_polar(int airspeed, _Q16 flap_angle, _Q16 brake_setting);

extern minifloat afrm_get_estimated_aoa(int airspeed, minifloat load);

extern int expected_glide_descent_rate(int airspeed, minifloat aoa);

// Calculate the expected climb rate depending on a throttle setting and airspeed
extern int feedforward_climb_rate(fractional throttle, int glide_descent_rate, int airspeed);


//typedef struct tag_aero_condition_list
//{
//	char listName[15];
//	const aero_condition_point*	pcond_list;
//	
//} aero_condition_list
//
//typedef struct tagAirframeDataMap
//{
//} AirframeDataMap;
//
//extern int condition_list_count[];
//extern int condition_list_sizes[];


#endif  // AIRFRAME_H
