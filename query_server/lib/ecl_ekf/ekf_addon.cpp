#include "ekf.h"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>
void Ekf::ekfSerializeToJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){
	rapidjson::Value yawObj(rapidjson::kObjectType);
	_yawEstimator.toJson(yawObj, allocator);
	ekfObj.AddMember("_yawEstimator", yawObj, allocator);
	rapidjson::Value baroObj(rapidjson::kObjectType);
	_baro_b_est.toJson(baroObj, allocator);
	ekfObj.AddMember("_baro_b_est", baroObj, allocator);
{
}
{
}
{
}
{
	{
		rapidjson::Value array_ang_rate_delayed_raw(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_ang_rate_delayed_raw.PushBack(_ang_rate_delayed_raw(i), allocator);
		}
		ekfObj.AddMember("_ang_rate_delayed_raw", array_ang_rate_delayed_raw, allocator);
	}
}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 4; i++){
				array_state.PushBack(_state.quat_nominal(i), allocator);
			}
			structObj.AddMember("quat_nominal", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_state.PushBack(_state.vel(i), allocator);
			}
			structObj.AddMember("vel", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_state.PushBack(_state.pos(i), allocator);
			}
			structObj.AddMember("pos", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_state.PushBack(_state.delta_ang_bias(i), allocator);
			}
			structObj.AddMember("delta_ang_bias", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_state.PushBack(_state.delta_vel_bias(i), allocator);
			}
			structObj.AddMember("delta_vel_bias", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_state.PushBack(_state.mag_I(i), allocator);
			}
			structObj.AddMember("mag_I", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				array_state.PushBack(_state.mag_B(i), allocator);
			}
			structObj.AddMember("mag_B", array_state, allocator);
		}
		{
			rapidjson::Value array_state(rapidjson::kArrayType);
			for(int i = 0; i < 2; i++){
				array_state.PushBack(_state.wind_vel(i), allocator);
			}
			structObj.AddMember("wind_vel", array_state, allocator);
		}
		ekfObj.AddMember("_state", structObj, allocator);
	}
{
	if (isnan(_filter_initialised)){
		ekfObj.AddMember("_filter_initialised", false, allocator);
	}else{
		ekfObj.AddMember("_filter_initialised", _filter_initialised, allocator);
	}
}
{
	if (isnan(_fuse_hpos_as_odom)){
		ekfObj.AddMember("_fuse_hpos_as_odom", false, allocator);
	}else{
		ekfObj.AddMember("_fuse_hpos_as_odom", _fuse_hpos_as_odom, allocator);
	}
}
{
	{
		rapidjson::Value array_hpos_pred_prev(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_hpos_pred_prev.PushBack(_hpos_pred_prev(i), allocator);
		}
		ekfObj.AddMember("_hpos_pred_prev", array_hpos_pred_prev, allocator);
	}
}
{
	if (isnan(_hpos_prev_available)){
		ekfObj.AddMember("_hpos_prev_available", false, allocator);
	}else{
		ekfObj.AddMember("_hpos_prev_available", _hpos_prev_available, allocator);
	}
}
{
	{
		rapidjson::Value array_R_ev_to_ekf(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				array_R_ev_to_ekf.PushBack(_R_ev_to_ekf(i, j), allocator);
			}
		}
		ekfObj.AddMember("_R_ev_to_ekf", array_R_ev_to_ekf, allocator);
	}
}
{
	if (isnan(_inhibit_ev_yaw_use)){
		ekfObj.AddMember("_inhibit_ev_yaw_use", false, allocator);
	}else{
		ekfObj.AddMember("_inhibit_ev_yaw_use", _inhibit_ev_yaw_use, allocator);
	}
}
{
	if (isnan(_gps_data_ready)){
		ekfObj.AddMember("_gps_data_ready", false, allocator);
	}else{
		ekfObj.AddMember("_gps_data_ready", _gps_data_ready, allocator);
	}
}
{
	if (isnan(_baro_data_ready)){
		ekfObj.AddMember("_baro_data_ready", false, allocator);
	}else{
		ekfObj.AddMember("_baro_data_ready", _baro_data_ready, allocator);
	}
}
{
	if (isnan(_flow_data_ready)){
		ekfObj.AddMember("_flow_data_ready", false, allocator);
	}else{
		ekfObj.AddMember("_flow_data_ready", _flow_data_ready, allocator);
	}
}
{
	if (isnan(_ev_data_ready)){
		ekfObj.AddMember("_ev_data_ready", false, allocator);
	}else{
		ekfObj.AddMember("_ev_data_ready", _ev_data_ready, allocator);
	}
}
{
	if (isnan(_tas_data_ready)){
		ekfObj.AddMember("_tas_data_ready", false, allocator);
	}else{
		ekfObj.AddMember("_tas_data_ready", _tas_data_ready, allocator);
	}
}
{
	if (isnan(_flow_for_terrain_data_ready)){
		ekfObj.AddMember("_flow_for_terrain_data_ready", false, allocator);
	}else{
		ekfObj.AddMember("_flow_for_terrain_data_ready", _flow_for_terrain_data_ready, allocator);
	}
}
{
	if (isnan(_time_prev_gps_us)){
		ekfObj.AddMember("_time_prev_gps_us", false, allocator);
	}else{
		ekfObj.AddMember("_time_prev_gps_us", _time_prev_gps_us, allocator);
	}
}
{
	if (isnan(_time_last_aiding)){
		ekfObj.AddMember("_time_last_aiding", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_aiding", _time_last_aiding, allocator);
	}
}
{
	if (isnan(_using_synthetic_position)){
		ekfObj.AddMember("_using_synthetic_position", false, allocator);
	}else{
		ekfObj.AddMember("_using_synthetic_position", _using_synthetic_position, allocator);
	}
}
{
	if (isnan(_time_last_hor_pos_fuse)){
		ekfObj.AddMember("_time_last_hor_pos_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_hor_pos_fuse", _time_last_hor_pos_fuse, allocator);
	}
}
{
	if (isnan(_time_last_hgt_fuse)){
		ekfObj.AddMember("_time_last_hgt_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_hgt_fuse", _time_last_hgt_fuse, allocator);
	}
}
{
	if (isnan(_time_last_hor_vel_fuse)){
		ekfObj.AddMember("_time_last_hor_vel_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_hor_vel_fuse", _time_last_hor_vel_fuse, allocator);
	}
}
{
	if (isnan(_time_last_ver_vel_fuse)){
		ekfObj.AddMember("_time_last_ver_vel_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_ver_vel_fuse", _time_last_ver_vel_fuse, allocator);
	}
}
{
	if (isnan(_time_last_of_fuse)){
		ekfObj.AddMember("_time_last_of_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_of_fuse", _time_last_of_fuse, allocator);
	}
}
{
	if (isnan(_time_last_flow_terrain_fuse)){
		ekfObj.AddMember("_time_last_flow_terrain_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_flow_terrain_fuse", _time_last_flow_terrain_fuse, allocator);
	}
}
{
	if (isnan(_time_last_arsp_fuse)){
		ekfObj.AddMember("_time_last_arsp_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_arsp_fuse", _time_last_arsp_fuse, allocator);
	}
}
{
	if (isnan(_time_last_beta_fuse)){
		ekfObj.AddMember("_time_last_beta_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_beta_fuse", _time_last_beta_fuse, allocator);
	}
}
{
	if (isnan(_time_last_fake_pos_fuse)){
		ekfObj.AddMember("_time_last_fake_pos_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_fake_pos_fuse", _time_last_fake_pos_fuse, allocator);
	}
}
{
	if (isnan(_time_last_zero_velocity_fuse)){
		ekfObj.AddMember("_time_last_zero_velocity_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_zero_velocity_fuse", _time_last_zero_velocity_fuse, allocator);
	}
}
{
	if (isnan(_time_last_gps_yaw_fuse)){
		ekfObj.AddMember("_time_last_gps_yaw_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_gps_yaw_fuse", _time_last_gps_yaw_fuse, allocator);
	}
}
{
	if (isnan(_time_last_gps_yaw_data)){
		ekfObj.AddMember("_time_last_gps_yaw_data", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_gps_yaw_data", _time_last_gps_yaw_data, allocator);
	}
}
{
	if (isnan(_time_last_healthy_rng_data)){
		ekfObj.AddMember("_time_last_healthy_rng_data", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_healthy_rng_data", _time_last_healthy_rng_data, allocator);
	}
}
{
	if (isnan(_nb_gps_yaw_reset_available)){
		ekfObj.AddMember("_nb_gps_yaw_reset_available", false, allocator);
	}else{
		ekfObj.AddMember("_nb_gps_yaw_reset_available", _nb_gps_yaw_reset_available, allocator);
	}
}
{
	{
		rapidjson::Value array_last_known_posNE(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_last_known_posNE.PushBack(_last_known_posNE(i), allocator);
		}
		ekfObj.AddMember("_last_known_posNE", array_last_known_posNE, allocator);
	}
}
{
	if (isnan(_time_acc_bias_check)){
		ekfObj.AddMember("_time_acc_bias_check", false, allocator);
	}else{
		ekfObj.AddMember("_time_acc_bias_check", _time_acc_bias_check, allocator);
	}
}
{
	if (isnan(_delta_time_baro_us)){
		ekfObj.AddMember("_delta_time_baro_us", false, allocator);
	}else{
		ekfObj.AddMember("_delta_time_baro_us", _delta_time_baro_us, allocator);
	}
}
{
	{
		rapidjson::Value array_earth_rate_NED(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_earth_rate_NED.PushBack(_earth_rate_NED(i), allocator);
		}
		ekfObj.AddMember("_earth_rate_NED", array_earth_rate_NED, allocator);
	}
}
{
	{
		rapidjson::Value array_R_to_earth(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				array_R_to_earth.PushBack(_R_to_earth(i, j), allocator);
			}
		}
		ekfObj.AddMember("_R_to_earth", array_R_to_earth, allocator);
	}
}
{
	{
		rapidjson::Value array_accel_lpf_NE(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_accel_lpf_NE.PushBack(_accel_lpf_NE(i), allocator);
		}
		ekfObj.AddMember("_accel_lpf_NE", array_accel_lpf_NE, allocator);
	}
}
{
	if (isnan(_yaw_delta_ef)){
		ekfObj.AddMember("_yaw_delta_ef", false, allocator);
	}else{
		ekfObj.AddMember("_yaw_delta_ef", _yaw_delta_ef, allocator);
	}
}
{
	if (isnan(_yaw_rate_lpf_ef)){
		ekfObj.AddMember("_yaw_rate_lpf_ef", false, allocator);
	}else{
		ekfObj.AddMember("_yaw_rate_lpf_ef", _yaw_rate_lpf_ef, allocator);
	}
}
{
	if (isnan(_mag_bias_observable)){
		ekfObj.AddMember("_mag_bias_observable", false, allocator);
	}else{
		ekfObj.AddMember("_mag_bias_observable", _mag_bias_observable, allocator);
	}
}
{
	if (isnan(_yaw_angle_observable)){
		ekfObj.AddMember("_yaw_angle_observable", false, allocator);
	}else{
		ekfObj.AddMember("_yaw_angle_observable", _yaw_angle_observable, allocator);
	}
}
{
	if (isnan(_time_yaw_started)){
		ekfObj.AddMember("_time_yaw_started", false, allocator);
	}else{
		ekfObj.AddMember("_time_yaw_started", _time_yaw_started, allocator);
	}
}
{
	if (isnan(_num_bad_flight_yaw_events)){
		ekfObj.AddMember("_num_bad_flight_yaw_events", false, allocator);
	}else{
		ekfObj.AddMember("_num_bad_flight_yaw_events", _num_bad_flight_yaw_events, allocator);
	}
}
{
	if (isnan(_mag_use_not_inhibit_us)){
		ekfObj.AddMember("_mag_use_not_inhibit_us", false, allocator);
	}else{
		ekfObj.AddMember("_mag_use_not_inhibit_us", _mag_use_not_inhibit_us, allocator);
	}
}
{
	if (isnan(_last_static_yaw)){
		ekfObj.AddMember("_last_static_yaw", false, allocator);
	}else{
		ekfObj.AddMember("_last_static_yaw", _last_static_yaw, allocator);
	}
}
{
	if (isnan(_mag_inhibit_yaw_reset_req)){
		ekfObj.AddMember("_mag_inhibit_yaw_reset_req", false, allocator);
	}else{
		ekfObj.AddMember("_mag_inhibit_yaw_reset_req", _mag_inhibit_yaw_reset_req, allocator);
	}
}
{
	if (isnan(_mag_yaw_reset_req)){
		ekfObj.AddMember("_mag_yaw_reset_req", false, allocator);
	}else{
		ekfObj.AddMember("_mag_yaw_reset_req", _mag_yaw_reset_req, allocator);
	}
}
{
	if (isnan(_mag_decl_cov_reset)){
		ekfObj.AddMember("_mag_decl_cov_reset", false, allocator);
	}else{
		ekfObj.AddMember("_mag_decl_cov_reset", _mag_decl_cov_reset, allocator);
	}
}
{
	if (isnan(_synthetic_mag_z_active)){
		ekfObj.AddMember("_synthetic_mag_z_active", false, allocator);
	}else{
		ekfObj.AddMember("_synthetic_mag_z_active", _synthetic_mag_z_active, allocator);
	}
}
{
	if (isnan(_non_mag_yaw_aiding_running_prev)){
		ekfObj.AddMember("_non_mag_yaw_aiding_running_prev", false, allocator);
	}else{
		ekfObj.AddMember("_non_mag_yaw_aiding_running_prev", _non_mag_yaw_aiding_running_prev, allocator);
	}
}
{
	if (isnan(_is_yaw_fusion_inhibited)){
		ekfObj.AddMember("_is_yaw_fusion_inhibited", false, allocator);
	}else{
		ekfObj.AddMember("_is_yaw_fusion_inhibited", _is_yaw_fusion_inhibited, allocator);
	}
}
{
	{
		rapidjson::Value arrayP(rapidjson::kArrayType);
		for(int i = 0; i < 24; i++){
			for(int j = 0; j < 24; j++){
				arrayP.PushBack(P(i, j), allocator);
			}
		}
		ekfObj.AddMember("P", arrayP, allocator);
	}
}
{
	{
		rapidjson::Value array_delta_vel_bias_var_accum(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_delta_vel_bias_var_accum.PushBack(_delta_vel_bias_var_accum(i), allocator);
		}
		ekfObj.AddMember("_delta_vel_bias_var_accum", array_delta_vel_bias_var_accum, allocator);
	}
}
{
	{
		rapidjson::Value array_delta_angle_bias_var_accum(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_delta_angle_bias_var_accum.PushBack(_delta_angle_bias_var_accum(i), allocator);
		}
		ekfObj.AddMember("_delta_angle_bias_var_accum", array_delta_angle_bias_var_accum, allocator);
	}
}
{
	if (isnan(_vert_pos_innov_ratio)){
		ekfObj.AddMember("_vert_pos_innov_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_vert_pos_innov_ratio", _vert_pos_innov_ratio, allocator);
	}
}
{
	if (isnan(_vert_pos_fuse_attempt_time_us)){
		ekfObj.AddMember("_vert_pos_fuse_attempt_time_us", false, allocator);
	}else{
		ekfObj.AddMember("_vert_pos_fuse_attempt_time_us", _vert_pos_fuse_attempt_time_us, allocator);
	}
}
{
	if (isnan(_vert_vel_innov_ratio)){
		ekfObj.AddMember("_vert_vel_innov_ratio", false, allocator);
	}else{
		ekfObj.AddMember("_vert_vel_innov_ratio", _vert_vel_innov_ratio, allocator);
	}
}
{
	if (isnan(_vert_vel_fuse_time_us)){
		ekfObj.AddMember("_vert_vel_fuse_time_us", false, allocator);
	}else{
		ekfObj.AddMember("_vert_vel_fuse_time_us", _vert_vel_fuse_time_us, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_vel_innov(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_gps_vel_innov.PushBack(_gps_vel_innov(i), allocator);
		}
		ekfObj.AddMember("_gps_vel_innov", array_gps_vel_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_vel_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_gps_vel_innov_var.PushBack(_gps_vel_innov_var(i), allocator);
		}
		ekfObj.AddMember("_gps_vel_innov_var", array_gps_vel_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_pos_innov(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_gps_pos_innov.PushBack(_gps_pos_innov(i), allocator);
		}
		ekfObj.AddMember("_gps_pos_innov", array_gps_pos_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_pos_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_gps_pos_innov_var.PushBack(_gps_pos_innov_var(i), allocator);
		}
		ekfObj.AddMember("_gps_pos_innov_var", array_gps_pos_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_ev_vel_innov(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_ev_vel_innov.PushBack(_ev_vel_innov(i), allocator);
		}
		ekfObj.AddMember("_ev_vel_innov", array_ev_vel_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_ev_vel_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_ev_vel_innov_var.PushBack(_ev_vel_innov_var(i), allocator);
		}
		ekfObj.AddMember("_ev_vel_innov_var", array_ev_vel_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_ev_pos_innov(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_ev_pos_innov.PushBack(_ev_pos_innov(i), allocator);
		}
		ekfObj.AddMember("_ev_pos_innov", array_ev_pos_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_ev_pos_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_ev_pos_innov_var.PushBack(_ev_pos_innov_var(i), allocator);
		}
		ekfObj.AddMember("_ev_pos_innov_var", array_ev_pos_innov_var, allocator);
	}
}
{
	if (isnan(_baro_hgt_innov)){
		ekfObj.AddMember("_baro_hgt_innov", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_innov", _baro_hgt_innov, allocator);
	}
}
{
	if (isnan(_baro_hgt_innov_var)){
		ekfObj.AddMember("_baro_hgt_innov_var", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_innov_var", _baro_hgt_innov_var, allocator);
	}
}
{
	if (isnan(_rng_hgt_innov)){
		ekfObj.AddMember("_rng_hgt_innov", false, allocator);
	}else{
		ekfObj.AddMember("_rng_hgt_innov", _rng_hgt_innov, allocator);
	}
}
{
	if (isnan(_rng_hgt_innov_var)){
		ekfObj.AddMember("_rng_hgt_innov_var", false, allocator);
	}else{
		ekfObj.AddMember("_rng_hgt_innov_var", _rng_hgt_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_aux_vel_innov(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_aux_vel_innov.PushBack(_aux_vel_innov(i), allocator);
		}
		ekfObj.AddMember("_aux_vel_innov", array_aux_vel_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_aux_vel_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_aux_vel_innov_var.PushBack(_aux_vel_innov_var(i), allocator);
		}
		ekfObj.AddMember("_aux_vel_innov_var", array_aux_vel_innov_var, allocator);
	}
}
{
	if (isnan(_heading_innov)){
		ekfObj.AddMember("_heading_innov", false, allocator);
	}else{
		ekfObj.AddMember("_heading_innov", _heading_innov, allocator);
	}
}
{
	if (isnan(_heading_innov_var)){
		ekfObj.AddMember("_heading_innov_var", false, allocator);
	}else{
		ekfObj.AddMember("_heading_innov_var", _heading_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_mag_innov(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_mag_innov.PushBack(_mag_innov(i), allocator);
		}
		ekfObj.AddMember("_mag_innov", array_mag_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_mag_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_mag_innov_var.PushBack(_mag_innov_var(i), allocator);
		}
		ekfObj.AddMember("_mag_innov_var", array_mag_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_drag_innov(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_drag_innov.PushBack(_drag_innov(i), allocator);
		}
		ekfObj.AddMember("_drag_innov", array_drag_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_drag_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_drag_innov_var.PushBack(_drag_innov_var(i), allocator);
		}
		ekfObj.AddMember("_drag_innov_var", array_drag_innov_var, allocator);
	}
}
{
	if (isnan(_airspeed_innov)){
		ekfObj.AddMember("_airspeed_innov", false, allocator);
	}else{
		ekfObj.AddMember("_airspeed_innov", _airspeed_innov, allocator);
	}
}
{
	if (isnan(_airspeed_innov_var)){
		ekfObj.AddMember("_airspeed_innov_var", false, allocator);
	}else{
		ekfObj.AddMember("_airspeed_innov_var", _airspeed_innov_var, allocator);
	}
}
{
	if (isnan(_beta_innov)){
		ekfObj.AddMember("_beta_innov", false, allocator);
	}else{
		ekfObj.AddMember("_beta_innov", _beta_innov, allocator);
	}
}
{
	if (isnan(_beta_innov_var)){
		ekfObj.AddMember("_beta_innov_var", false, allocator);
	}else{
		ekfObj.AddMember("_beta_innov_var", _beta_innov_var, allocator);
	}
}
{
	if (isnan(_hagl_innov)){
		ekfObj.AddMember("_hagl_innov", false, allocator);
	}else{
		ekfObj.AddMember("_hagl_innov", _hagl_innov, allocator);
	}
}
{
	if (isnan(_hagl_innov_var)){
		ekfObj.AddMember("_hagl_innov_var", false, allocator);
	}else{
		ekfObj.AddMember("_hagl_innov_var", _hagl_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_flow_innov(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_flow_innov.PushBack(_flow_innov(i), allocator);
		}
		ekfObj.AddMember("_flow_innov", array_flow_innov, allocator);
	}
}
{
	{
		rapidjson::Value array_flow_innov_var(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_flow_innov_var.PushBack(_flow_innov_var(i), allocator);
		}
		ekfObj.AddMember("_flow_innov_var", array_flow_innov_var, allocator);
	}
}
{
	{
		rapidjson::Value array_flow_gyro_bias(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_flow_gyro_bias.PushBack(_flow_gyro_bias(i), allocator);
		}
		ekfObj.AddMember("_flow_gyro_bias", array_flow_gyro_bias, allocator);
	}
}
{
	{
		rapidjson::Value array_flow_vel_body(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_flow_vel_body.PushBack(_flow_vel_body(i), allocator);
		}
		ekfObj.AddMember("_flow_vel_body", array_flow_vel_body, allocator);
	}
}
{
	{
		rapidjson::Value array_flow_vel_ne(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_flow_vel_ne.PushBack(_flow_vel_ne(i), allocator);
		}
		ekfObj.AddMember("_flow_vel_ne", array_flow_vel_ne, allocator);
	}
}
{
	{
		rapidjson::Value array_imu_del_ang_of(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_imu_del_ang_of.PushBack(_imu_del_ang_of(i), allocator);
		}
		ekfObj.AddMember("_imu_del_ang_of", array_imu_del_ang_of, allocator);
	}
}
{
	if (isnan(_delta_time_of)){
		ekfObj.AddMember("_delta_time_of", false, allocator);
	}else{
		ekfObj.AddMember("_delta_time_of", _delta_time_of, allocator);
	}
}
{
	if (isnan(_time_bad_motion_us)){
		ekfObj.AddMember("_time_bad_motion_us", false, allocator);
	}else{
		ekfObj.AddMember("_time_bad_motion_us", _time_bad_motion_us, allocator);
	}
}
{
	if (isnan(_time_good_motion_us)){
		ekfObj.AddMember("_time_good_motion_us", false, allocator);
	}else{
		ekfObj.AddMember("_time_good_motion_us", _time_good_motion_us, allocator);
	}
}
{
	if (isnan(_inhibit_flow_use)){
		ekfObj.AddMember("_inhibit_flow_use", false, allocator);
	}else{
		ekfObj.AddMember("_inhibit_flow_use", _inhibit_flow_use, allocator);
	}
}
{
	{
		rapidjson::Value array_flow_compensated_XY_rad(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_flow_compensated_XY_rad.PushBack(_flow_compensated_XY_rad(i), allocator);
		}
		ekfObj.AddMember("_flow_compensated_XY_rad", array_flow_compensated_XY_rad, allocator);
	}
}
{
	{
		rapidjson::Value array_delta_angle_corr(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_delta_angle_corr.PushBack(_delta_angle_corr(i), allocator);
		}
		ekfObj.AddMember("_delta_angle_corr", array_delta_angle_corr, allocator);
	}
}
{
	{
		rapidjson::Value array_vel_err_integ(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_vel_err_integ.PushBack(_vel_err_integ(i), allocator);
		}
		ekfObj.AddMember("_vel_err_integ", array_vel_err_integ, allocator);
	}
}
{
	{
		rapidjson::Value array_pos_err_integ(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_pos_err_integ.PushBack(_pos_err_integ(i), allocator);
		}
		ekfObj.AddMember("_pos_err_integ", array_pos_err_integ, allocator);
	}
}
{
	{
		rapidjson::Value array_output_tracking_error(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_output_tracking_error.PushBack(_output_tracking_error(i), allocator);
		}
		ekfObj.AddMember("_output_tracking_error", array_output_tracking_error, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_pos_deriv_filt(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_gps_pos_deriv_filt.PushBack(_gps_pos_deriv_filt(i), allocator);
		}
		ekfObj.AddMember("_gps_pos_deriv_filt", array_gps_pos_deriv_filt, allocator);
	}
}
{
	{
		rapidjson::Value array_gps_velNE_filt(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			array_gps_velNE_filt.PushBack(_gps_velNE_filt(i), allocator);
		}
		ekfObj.AddMember("_gps_velNE_filt", array_gps_velNE_filt, allocator);
	}
}
{
	if (isnan(_gps_velD_diff_filt)){
		ekfObj.AddMember("_gps_velD_diff_filt", false, allocator);
	}else{
		ekfObj.AddMember("_gps_velD_diff_filt", _gps_velD_diff_filt, allocator);
	}
}
{
	if (isnan(_last_gps_fail_us)){
		ekfObj.AddMember("_last_gps_fail_us", false, allocator);
	}else{
		ekfObj.AddMember("_last_gps_fail_us", _last_gps_fail_us, allocator);
	}
}
{
	if (isnan(_last_gps_pass_us)){
		ekfObj.AddMember("_last_gps_pass_us", false, allocator);
	}else{
		ekfObj.AddMember("_last_gps_pass_us", _last_gps_pass_us, allocator);
	}
}
{
	if (isnan(_gps_error_norm)){
		ekfObj.AddMember("_gps_error_norm", false, allocator);
	}else{
		ekfObj.AddMember("_gps_error_norm", _gps_error_norm, allocator);
	}
}
{
	if (isnan(_min_gps_health_time_us)){
		ekfObj.AddMember("_min_gps_health_time_us", false, allocator);
	}else{
		ekfObj.AddMember("_min_gps_health_time_us", _min_gps_health_time_us, allocator);
	}
}
{
	if (isnan(_gps_checks_passed)){
		ekfObj.AddMember("_gps_checks_passed", false, allocator);
	}else{
		ekfObj.AddMember("_gps_checks_passed", _gps_checks_passed, allocator);
	}
}
{
	if (isnan(_last_gps_origin_time_us)){
		ekfObj.AddMember("_last_gps_origin_time_us", false, allocator);
	}else{
		ekfObj.AddMember("_last_gps_origin_time_us", _last_gps_origin_time_us, allocator);
	}
}
{
	if (isnan(_gps_alt_ref)){
		ekfObj.AddMember("_gps_alt_ref", false, allocator);
	}else{
		ekfObj.AddMember("_gps_alt_ref", _gps_alt_ref, allocator);
	}
}
{
	if (isnan(_is_first_imu_sample)){
		ekfObj.AddMember("_is_first_imu_sample", false, allocator);
	}else{
		ekfObj.AddMember("_is_first_imu_sample", _is_first_imu_sample, allocator);
	}
}
{
	if (isnan(_baro_counter)){
		ekfObj.AddMember("_baro_counter", false, allocator);
	}else{
		ekfObj.AddMember("_baro_counter", _baro_counter, allocator);
	}
}
{
	if (isnan(_mag_counter)){
		ekfObj.AddMember("_mag_counter", false, allocator);
	}else{
		ekfObj.AddMember("_mag_counter", _mag_counter, allocator);
	}
}
	{
		rapidjson::Value Vector3fAF(rapidjson::kObjectType);
		Vector3fAF.AddMember("_cutoff_freq", _accel_lpf.getCutoffFreq(), allocator);
		Vector3fAF.AddMember("_alpha", _accel_lpf.getAlpha(), allocator);
		auto & fs = _accel_lpf.getState();
		{
			rapidjson::Value _accel_lpf_filter_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				_accel_lpf_filter_state.PushBack(fs(i), allocator);
			}
			Vector3fAF.AddMember("_filter_state", _accel_lpf_filter_state, allocator);
		}
		ekfObj.AddMember("_accel_lpf", Vector3fAF, allocator);
	}
	{
		rapidjson::Value Vector3fAF(rapidjson::kObjectType);
		Vector3fAF.AddMember("_cutoff_freq", _gyro_lpf.getCutoffFreq(), allocator);
		Vector3fAF.AddMember("_alpha", _gyro_lpf.getAlpha(), allocator);
		auto & fs = _gyro_lpf.getState();
		{
			rapidjson::Value _gyro_lpf_filter_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				_gyro_lpf_filter_state.PushBack(fs(i), allocator);
			}
			Vector3fAF.AddMember("_filter_state", _gyro_lpf_filter_state, allocator);
		}
		ekfObj.AddMember("_gyro_lpf", Vector3fAF, allocator);
	}
	{
		rapidjson::Value Vector3fAF(rapidjson::kObjectType);
		Vector3fAF.AddMember("_cutoff_freq", _mag_lpf.getCutoffFreq(), allocator);
		Vector3fAF.AddMember("_alpha", _mag_lpf.getAlpha(), allocator);
		auto & fs = _mag_lpf.getState();
		{
			rapidjson::Value _mag_lpf_filter_state(rapidjson::kArrayType);
			for(int i = 0; i < 3; i++){
				_mag_lpf_filter_state.PushBack(fs(i), allocator);
			}
			Vector3fAF.AddMember("_filter_state", _mag_lpf_filter_state, allocator);
		}
		ekfObj.AddMember("_mag_lpf", Vector3fAF, allocator);
	}
{
	if (isnan(_hgt_sensor_offset)){
		ekfObj.AddMember("_hgt_sensor_offset", false, allocator);
	}else{
		ekfObj.AddMember("_hgt_sensor_offset", _hgt_sensor_offset, allocator);
	}
}
{
	if (isnan(_baro_hgt_offset)){
		ekfObj.AddMember("_baro_hgt_offset", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_offset", _baro_hgt_offset, allocator);
	}
}
{
	if (isnan(_baro_hgt_bias)){
		ekfObj.AddMember("_baro_hgt_bias", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_bias", _baro_hgt_bias, allocator);
	}
}
{
	if (isnan(_baro_hgt_bias_var)){
		ekfObj.AddMember("_baro_hgt_bias_var", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_bias_var", _baro_hgt_bias_var, allocator);
	}
}
{
	if (isnan(_last_on_ground_posD)){
		ekfObj.AddMember("_last_on_ground_posD", false, allocator);
	}else{
		ekfObj.AddMember("_last_on_ground_posD", _last_on_ground_posD, allocator);
	}
}
{
	if (isnan(_flt_mag_align_start_time)){
		ekfObj.AddMember("_flt_mag_align_start_time", false, allocator);
	}else{
		ekfObj.AddMember("_flt_mag_align_start_time", _flt_mag_align_start_time, allocator);
	}
}
{
	if (isnan(_time_last_mov_3d_mag_suitable)){
		ekfObj.AddMember("_time_last_mov_3d_mag_suitable", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_mov_3d_mag_suitable", _time_last_mov_3d_mag_suitable, allocator);
	}
}
{
	{
		rapidjson::Value array_saved_mag_bf_variance(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_saved_mag_bf_variance.PushBack(_saved_mag_bf_variance(i), allocator);
		}
		ekfObj.AddMember("_saved_mag_bf_variance", array_saved_mag_bf_variance, allocator);
	}
}
{
	{
		rapidjson::Value array_saved_mag_ef_ne_covmat(rapidjson::kArrayType);
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				array_saved_mag_ef_ne_covmat.PushBack(_saved_mag_ef_ne_covmat(i, j), allocator);
			}
		}
		ekfObj.AddMember("_saved_mag_ef_ne_covmat", array_saved_mag_ef_ne_covmat, allocator);
	}
}
{
	if (isnan(_saved_mag_ef_d_variance)){
		ekfObj.AddMember("_saved_mag_ef_d_variance", false, allocator);
	}else{
		ekfObj.AddMember("_saved_mag_ef_d_variance", _saved_mag_ef_d_variance, allocator);
	}
}
	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		if(_gps_check_fail_status.flags.fix){
			innerJson.AddMember("fix", true, allocator);
		}else{
			innerJson.AddMember("fix", false, allocator);
		}
		if(_gps_check_fail_status.flags.hacc){
			innerJson.AddMember("hacc", true, allocator);
		}else{
			innerJson.AddMember("hacc", false, allocator);
		}
		if(_gps_check_fail_status.flags.hdrift){
			innerJson.AddMember("hdrift", true, allocator);
		}else{
			innerJson.AddMember("hdrift", false, allocator);
		}
		if(_gps_check_fail_status.flags.hspeed){
			innerJson.AddMember("hspeed", true, allocator);
		}else{
			innerJson.AddMember("hspeed", false, allocator);
		}
		if(_gps_check_fail_status.flags.nsats){
			innerJson.AddMember("nsats", true, allocator);
		}else{
			innerJson.AddMember("nsats", false, allocator);
		}
		if(_gps_check_fail_status.flags.pdop){
			innerJson.AddMember("pdop", true, allocator);
		}else{
			innerJson.AddMember("pdop", false, allocator);
		}
		if(_gps_check_fail_status.flags.sacc){
			innerJson.AddMember("sacc", true, allocator);
		}else{
			innerJson.AddMember("sacc", false, allocator);
		}
		if(_gps_check_fail_status.flags.vacc){
			innerJson.AddMember("vacc", true, allocator);
		}else{
			innerJson.AddMember("vacc", false, allocator);
		}
		if(_gps_check_fail_status.flags.vdrift){
			innerJson.AddMember("vdrift", true, allocator);
		}else{
			innerJson.AddMember("vdrift", false, allocator);
		}
		if(_gps_check_fail_status.flags.vspeed){
			innerJson.AddMember("vspeed", true, allocator);
		}else{
			innerJson.AddMember("vspeed", false, allocator);
		}
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_gps_check_fail_status", unionJson, allocator);
	}{
	{
		rapidjson::Value array_accel_bias_inhibit(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_accel_bias_inhibit.PushBack(_accel_bias_inhibit[i], allocator);
		}
		ekfObj.AddMember("_accel_bias_inhibit", array_accel_bias_inhibit, allocator);
	}
}
{
	{
		rapidjson::Value array_accel_vec_filt(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_accel_vec_filt.PushBack(_accel_vec_filt(i), allocator);
		}
		ekfObj.AddMember("_accel_vec_filt", array_accel_vec_filt, allocator);
	}
}
{
	if (isnan(_accel_magnitude_filt)){
		ekfObj.AddMember("_accel_magnitude_filt", false, allocator);
	}else{
		ekfObj.AddMember("_accel_magnitude_filt", _accel_magnitude_filt, allocator);
	}
}
{
	if (isnan(_ang_rate_magnitude_filt)){
		ekfObj.AddMember("_ang_rate_magnitude_filt", false, allocator);
	}else{
		ekfObj.AddMember("_ang_rate_magnitude_filt", _ang_rate_magnitude_filt, allocator);
	}
}
{
	{
		rapidjson::Value array_prev_dvel_bias_var(rapidjson::kArrayType);
		for(int i = 0; i < 3; i++){
			array_prev_dvel_bias_var.PushBack(_prev_dvel_bias_var(i), allocator);
		}
		ekfObj.AddMember("_prev_dvel_bias_var", array_prev_dvel_bias_var, allocator);
	}
}
{
	if (isnan(_terrain_vpos)){
		ekfObj.AddMember("_terrain_vpos", false, allocator);
	}else{
		ekfObj.AddMember("_terrain_vpos", _terrain_vpos, allocator);
	}
}
{
	if (isnan(_terrain_var)){
		ekfObj.AddMember("_terrain_var", false, allocator);
	}else{
		ekfObj.AddMember("_terrain_var", _terrain_var, allocator);
	}
}
{
	if (isnan(_terrain_vpos_reset_counter)){
		ekfObj.AddMember("_terrain_vpos_reset_counter", false, allocator);
	}else{
		ekfObj.AddMember("_terrain_vpos_reset_counter", _terrain_vpos_reset_counter, allocator);
	}
}
{
	if (isnan(_time_last_hagl_fuse)){
		ekfObj.AddMember("_time_last_hagl_fuse", false, allocator);
	}else{
		ekfObj.AddMember("_time_last_hagl_fuse", _time_last_hagl_fuse, allocator);
	}
}
{
	if (isnan(_hagl_valid)){
		ekfObj.AddMember("_hagl_valid", false, allocator);
	}else{
		ekfObj.AddMember("_hagl_valid", _hagl_valid, allocator);
	}
}
	{
		rapidjson::Value unionJson(rapidjson::kObjectType);
		rapidjson::Value innerJson(rapidjson::kObjectType);
		innerJson.AddMember("flow", _hagl_sensor_status.flags.flow, allocator);
		innerJson.AddMember("range_finder", _hagl_sensor_status.flags.range_finder, allocator);
		unionJson.AddMember("flags", innerJson, allocator);
		ekfObj.AddMember("_hagl_sensor_status", unionJson, allocator);
	}{
	if (isnan(_baro_hgt_faulty)){
		ekfObj.AddMember("_baro_hgt_faulty", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_faulty", _baro_hgt_faulty, allocator);
	}
}
{
	if (isnan(_baro_hgt_intermittent)){
		ekfObj.AddMember("_baro_hgt_intermittent", false, allocator);
	}else{
		ekfObj.AddMember("_baro_hgt_intermittent", _baro_hgt_intermittent, allocator);
	}
}
{
	if (isnan(_gps_intermittent)){
		ekfObj.AddMember("_gps_intermittent", false, allocator);
	}else{
		ekfObj.AddMember("_gps_intermittent", _gps_intermittent, allocator);
	}
}
{
	if (isnan(_time_bad_vert_accel)){
		ekfObj.AddMember("_time_bad_vert_accel", false, allocator);
	}else{
		ekfObj.AddMember("_time_bad_vert_accel", _time_bad_vert_accel, allocator);
	}
}
{
	if (isnan(_time_good_vert_accel)){
		ekfObj.AddMember("_time_good_vert_accel", false, allocator);
	}else{
		ekfObj.AddMember("_time_good_vert_accel", _time_good_vert_accel, allocator);
	}
}
{
	if (isnan(_clip_counter)){
		ekfObj.AddMember("_clip_counter", false, allocator);
	}else{
		ekfObj.AddMember("_clip_counter", _clip_counter, allocator);
	}
}
{
	if (isnan(_is_range_aid_suitable)){
		ekfObj.AddMember("_is_range_aid_suitable", false, allocator);
	}else{
		ekfObj.AddMember("_is_range_aid_suitable", _is_range_aid_suitable, allocator);
	}
}
{
	if (isnan(_height_rate_lpf)){
		ekfObj.AddMember("_height_rate_lpf", false, allocator);
	}else{
		ekfObj.AddMember("_height_rate_lpf", _height_rate_lpf, allocator);
	}
}
{
}
{
}
{
	if (isnan(_ekfgsf_yaw_reset_time)){
		ekfObj.AddMember("_ekfgsf_yaw_reset_time", false, allocator);
	}else{
		ekfObj.AddMember("_ekfgsf_yaw_reset_time", _ekfgsf_yaw_reset_time, allocator);
	}
}
{
	if (isnan(_ekfgsf_yaw_reset_count)){
		ekfObj.AddMember("_ekfgsf_yaw_reset_count", false, allocator);
	}else{
		ekfObj.AddMember("_ekfgsf_yaw_reset_count", _ekfgsf_yaw_reset_count, allocator);
	}
}

}
void Ekf::ekfCheckJson(rapidjson::Value & ekfObj){
				assert(ekfObj.HasMember("_ang_rate_delayed_raw"));
assert(ekfObj["_ang_rate_delayed_raw"].IsArray());
{
	assert(ekfObj["_state"].IsObject());
	assert(ekfObj["_state"]["quat_nominal"].IsArray());
	assert(ekfObj["_state"]["vel"].IsArray());
	assert(ekfObj["_state"]["pos"].IsArray());
	assert(ekfObj["_state"]["delta_ang_bias"].IsArray());
	assert(ekfObj["_state"]["delta_vel_bias"].IsArray());
	assert(ekfObj["_state"]["mag_I"].IsArray());
	assert(ekfObj["_state"]["mag_B"].IsArray());
	assert(ekfObj["_state"]["wind_vel"].IsArray());
}
	assert(ekfObj.HasMember("_filter_initialised"));
assert(ekfObj["_filter_initialised"].IsBool());
	assert(ekfObj.HasMember("_fuse_hpos_as_odom"));
assert(ekfObj["_fuse_hpos_as_odom"].IsBool());
	assert(ekfObj.HasMember("_hpos_pred_prev"));
assert(ekfObj["_hpos_pred_prev"].IsArray());
	assert(ekfObj.HasMember("_hpos_prev_available"));
assert(ekfObj["_hpos_prev_available"].IsBool());
	assert(ekfObj.HasMember("_R_ev_to_ekf"));
assert(ekfObj["_R_ev_to_ekf"].IsArray());
	assert(ekfObj.HasMember("_inhibit_ev_yaw_use"));
assert(ekfObj["_inhibit_ev_yaw_use"].IsBool());
	assert(ekfObj.HasMember("_gps_data_ready"));
assert(ekfObj["_gps_data_ready"].IsBool());
	assert(ekfObj.HasMember("_baro_data_ready"));
assert(ekfObj["_baro_data_ready"].IsBool());
	assert(ekfObj.HasMember("_flow_data_ready"));
assert(ekfObj["_flow_data_ready"].IsBool());
	assert(ekfObj.HasMember("_ev_data_ready"));
assert(ekfObj["_ev_data_ready"].IsBool());
	assert(ekfObj.HasMember("_tas_data_ready"));
assert(ekfObj["_tas_data_ready"].IsBool());
	assert(ekfObj.HasMember("_flow_for_terrain_data_ready"));
assert(ekfObj["_flow_for_terrain_data_ready"].IsBool());
	assert(ekfObj.HasMember("_time_prev_gps_us"));
assert(ekfObj["_time_prev_gps_us"].IsUint64());
	assert(ekfObj.HasMember("_time_last_aiding"));
assert(ekfObj["_time_last_aiding"].IsUint64());
	assert(ekfObj.HasMember("_using_synthetic_position"));
assert(ekfObj["_using_synthetic_position"].IsBool());
	assert(ekfObj.HasMember("_time_last_hor_pos_fuse"));
assert(ekfObj["_time_last_hor_pos_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_hgt_fuse"));
assert(ekfObj["_time_last_hgt_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_hor_vel_fuse"));
assert(ekfObj["_time_last_hor_vel_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_ver_vel_fuse"));
assert(ekfObj["_time_last_ver_vel_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_of_fuse"));
assert(ekfObj["_time_last_of_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_flow_terrain_fuse"));
assert(ekfObj["_time_last_flow_terrain_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_arsp_fuse"));
assert(ekfObj["_time_last_arsp_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_beta_fuse"));
assert(ekfObj["_time_last_beta_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_fake_pos_fuse"));
assert(ekfObj["_time_last_fake_pos_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_zero_velocity_fuse"));
assert(ekfObj["_time_last_zero_velocity_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_gps_yaw_fuse"));
assert(ekfObj["_time_last_gps_yaw_fuse"].IsUint64());
	assert(ekfObj.HasMember("_time_last_gps_yaw_data"));
assert(ekfObj["_time_last_gps_yaw_data"].IsUint64());
	assert(ekfObj.HasMember("_time_last_healthy_rng_data"));
assert(ekfObj["_time_last_healthy_rng_data"].IsUint64());
	assert(ekfObj.HasMember("_nb_gps_yaw_reset_available"));
assert(ekfObj["_nb_gps_yaw_reset_available"].IsUint());
	assert(ekfObj.HasMember("_last_known_posNE"));
assert(ekfObj["_last_known_posNE"].IsArray());
	assert(ekfObj.HasMember("_time_acc_bias_check"));
assert(ekfObj["_time_acc_bias_check"].IsUint64());
	assert(ekfObj.HasMember("_delta_time_baro_us"));
assert(ekfObj["_delta_time_baro_us"].IsUint64());
	assert(ekfObj.HasMember("_earth_rate_NED"));
assert(ekfObj["_earth_rate_NED"].IsArray());
	assert(ekfObj.HasMember("_R_to_earth"));
assert(ekfObj["_R_to_earth"].IsArray());
	assert(ekfObj.HasMember("_accel_lpf_NE"));
assert(ekfObj["_accel_lpf_NE"].IsArray());
	assert(ekfObj.HasMember("_yaw_delta_ef"));
assert(ekfObj["_yaw_delta_ef"].IsFloat() || ekfObj["_yaw_delta_ef"].IsBool());
	assert(ekfObj.HasMember("_yaw_rate_lpf_ef"));
assert(ekfObj["_yaw_rate_lpf_ef"].IsFloat() || ekfObj["_yaw_rate_lpf_ef"].IsBool());
	assert(ekfObj.HasMember("_mag_bias_observable"));
assert(ekfObj["_mag_bias_observable"].IsBool());
	assert(ekfObj.HasMember("_yaw_angle_observable"));
assert(ekfObj["_yaw_angle_observable"].IsBool());
	assert(ekfObj.HasMember("_time_yaw_started"));
assert(ekfObj["_time_yaw_started"].IsUint64());
	assert(ekfObj.HasMember("_num_bad_flight_yaw_events"));
assert(ekfObj["_num_bad_flight_yaw_events"].IsUint());
	assert(ekfObj.HasMember("_mag_use_not_inhibit_us"));
assert(ekfObj["_mag_use_not_inhibit_us"].IsUint64());
	assert(ekfObj.HasMember("_last_static_yaw"));
assert(ekfObj["_last_static_yaw"].IsFloat() || ekfObj["_last_static_yaw"].IsBool());
	assert(ekfObj.HasMember("_mag_inhibit_yaw_reset_req"));
assert(ekfObj["_mag_inhibit_yaw_reset_req"].IsBool());
	assert(ekfObj.HasMember("_mag_yaw_reset_req"));
assert(ekfObj["_mag_yaw_reset_req"].IsBool());
	assert(ekfObj.HasMember("_mag_decl_cov_reset"));
assert(ekfObj["_mag_decl_cov_reset"].IsBool());
	assert(ekfObj.HasMember("_synthetic_mag_z_active"));
assert(ekfObj["_synthetic_mag_z_active"].IsBool());
	assert(ekfObj.HasMember("_non_mag_yaw_aiding_running_prev"));
assert(ekfObj["_non_mag_yaw_aiding_running_prev"].IsBool());
	assert(ekfObj.HasMember("_is_yaw_fusion_inhibited"));
assert(ekfObj["_is_yaw_fusion_inhibited"].IsBool());
	assert(ekfObj.HasMember("P"));
assert(ekfObj["P"].IsArray());
	assert(ekfObj.HasMember("_delta_vel_bias_var_accum"));
assert(ekfObj["_delta_vel_bias_var_accum"].IsArray());
	assert(ekfObj.HasMember("_delta_angle_bias_var_accum"));
assert(ekfObj["_delta_angle_bias_var_accum"].IsArray());
	assert(ekfObj.HasMember("_vert_pos_innov_ratio"));
assert(ekfObj["_vert_pos_innov_ratio"].IsFloat() || ekfObj["_vert_pos_innov_ratio"].IsBool());
	assert(ekfObj.HasMember("_vert_pos_fuse_attempt_time_us"));
assert(ekfObj["_vert_pos_fuse_attempt_time_us"].IsUint64());
	assert(ekfObj.HasMember("_vert_vel_innov_ratio"));
assert(ekfObj["_vert_vel_innov_ratio"].IsFloat() || ekfObj["_vert_vel_innov_ratio"].IsBool());
	assert(ekfObj.HasMember("_vert_vel_fuse_time_us"));
assert(ekfObj["_vert_vel_fuse_time_us"].IsUint64());
	assert(ekfObj.HasMember("_gps_vel_innov"));
assert(ekfObj["_gps_vel_innov"].IsArray());
	assert(ekfObj.HasMember("_gps_vel_innov_var"));
assert(ekfObj["_gps_vel_innov_var"].IsArray());
	assert(ekfObj.HasMember("_gps_pos_innov"));
assert(ekfObj["_gps_pos_innov"].IsArray());
	assert(ekfObj.HasMember("_gps_pos_innov_var"));
assert(ekfObj["_gps_pos_innov_var"].IsArray());
	assert(ekfObj.HasMember("_ev_vel_innov"));
assert(ekfObj["_ev_vel_innov"].IsArray());
	assert(ekfObj.HasMember("_ev_vel_innov_var"));
assert(ekfObj["_ev_vel_innov_var"].IsArray());
	assert(ekfObj.HasMember("_ev_pos_innov"));
assert(ekfObj["_ev_pos_innov"].IsArray());
	assert(ekfObj.HasMember("_ev_pos_innov_var"));
assert(ekfObj["_ev_pos_innov_var"].IsArray());
	assert(ekfObj.HasMember("_baro_hgt_innov"));
assert(ekfObj["_baro_hgt_innov"].IsFloat() || ekfObj["_baro_hgt_innov"].IsBool());
	assert(ekfObj.HasMember("_baro_hgt_innov_var"));
assert(ekfObj["_baro_hgt_innov_var"].IsFloat() || ekfObj["_baro_hgt_innov_var"].IsBool());
	assert(ekfObj.HasMember("_rng_hgt_innov"));
assert(ekfObj["_rng_hgt_innov"].IsFloat() || ekfObj["_rng_hgt_innov"].IsBool());
	assert(ekfObj.HasMember("_rng_hgt_innov_var"));
assert(ekfObj["_rng_hgt_innov_var"].IsFloat() || ekfObj["_rng_hgt_innov_var"].IsBool());
	assert(ekfObj.HasMember("_aux_vel_innov"));
assert(ekfObj["_aux_vel_innov"].IsArray());
	assert(ekfObj.HasMember("_aux_vel_innov_var"));
assert(ekfObj["_aux_vel_innov_var"].IsArray());
	assert(ekfObj.HasMember("_heading_innov"));
assert(ekfObj["_heading_innov"].IsFloat() || ekfObj["_heading_innov"].IsBool());
	assert(ekfObj.HasMember("_heading_innov_var"));
assert(ekfObj["_heading_innov_var"].IsFloat() || ekfObj["_heading_innov_var"].IsBool());
	assert(ekfObj.HasMember("_mag_innov"));
assert(ekfObj["_mag_innov"].IsArray());
	assert(ekfObj.HasMember("_mag_innov_var"));
assert(ekfObj["_mag_innov_var"].IsArray());
	assert(ekfObj.HasMember("_drag_innov"));
assert(ekfObj["_drag_innov"].IsArray());
	assert(ekfObj.HasMember("_drag_innov_var"));
assert(ekfObj["_drag_innov_var"].IsArray());
	assert(ekfObj.HasMember("_airspeed_innov"));
assert(ekfObj["_airspeed_innov"].IsFloat() || ekfObj["_airspeed_innov"].IsBool());
	assert(ekfObj.HasMember("_airspeed_innov_var"));
assert(ekfObj["_airspeed_innov_var"].IsFloat() || ekfObj["_airspeed_innov_var"].IsBool());
	assert(ekfObj.HasMember("_beta_innov"));
assert(ekfObj["_beta_innov"].IsFloat() || ekfObj["_beta_innov"].IsBool());
	assert(ekfObj.HasMember("_beta_innov_var"));
assert(ekfObj["_beta_innov_var"].IsFloat() || ekfObj["_beta_innov_var"].IsBool());
	assert(ekfObj.HasMember("_hagl_innov"));
assert(ekfObj["_hagl_innov"].IsFloat() || ekfObj["_hagl_innov"].IsBool());
	assert(ekfObj.HasMember("_hagl_innov_var"));
assert(ekfObj["_hagl_innov_var"].IsFloat() || ekfObj["_hagl_innov_var"].IsBool());
	assert(ekfObj.HasMember("_flow_innov"));
assert(ekfObj["_flow_innov"].IsArray());
	assert(ekfObj.HasMember("_flow_innov_var"));
assert(ekfObj["_flow_innov_var"].IsArray());
	assert(ekfObj.HasMember("_flow_gyro_bias"));
assert(ekfObj["_flow_gyro_bias"].IsArray());
	assert(ekfObj.HasMember("_flow_vel_body"));
assert(ekfObj["_flow_vel_body"].IsArray());
	assert(ekfObj.HasMember("_flow_vel_ne"));
assert(ekfObj["_flow_vel_ne"].IsArray());
	assert(ekfObj.HasMember("_imu_del_ang_of"));
assert(ekfObj["_imu_del_ang_of"].IsArray());
	assert(ekfObj.HasMember("_delta_time_of"));
assert(ekfObj["_delta_time_of"].IsFloat() || ekfObj["_delta_time_of"].IsBool());
	assert(ekfObj.HasMember("_time_bad_motion_us"));
assert(ekfObj["_time_bad_motion_us"].IsUint64());
	assert(ekfObj.HasMember("_time_good_motion_us"));
assert(ekfObj["_time_good_motion_us"].IsUint64());
	assert(ekfObj.HasMember("_inhibit_flow_use"));
assert(ekfObj["_inhibit_flow_use"].IsBool());
	assert(ekfObj.HasMember("_flow_compensated_XY_rad"));
assert(ekfObj["_flow_compensated_XY_rad"].IsArray());
	assert(ekfObj.HasMember("_delta_angle_corr"));
assert(ekfObj["_delta_angle_corr"].IsArray());
	assert(ekfObj.HasMember("_vel_err_integ"));
assert(ekfObj["_vel_err_integ"].IsArray());
	assert(ekfObj.HasMember("_pos_err_integ"));
assert(ekfObj["_pos_err_integ"].IsArray());
	assert(ekfObj.HasMember("_output_tracking_error"));
assert(ekfObj["_output_tracking_error"].IsArray());
	assert(ekfObj.HasMember("_gps_pos_deriv_filt"));
assert(ekfObj["_gps_pos_deriv_filt"].IsArray());
	assert(ekfObj.HasMember("_gps_velNE_filt"));
assert(ekfObj["_gps_velNE_filt"].IsArray());
	assert(ekfObj.HasMember("_gps_velD_diff_filt"));
assert(ekfObj["_gps_velD_diff_filt"].IsFloat() || ekfObj["_gps_velD_diff_filt"].IsBool());
	assert(ekfObj.HasMember("_last_gps_fail_us"));
assert(ekfObj["_last_gps_fail_us"].IsUint64());
	assert(ekfObj.HasMember("_last_gps_pass_us"));
assert(ekfObj["_last_gps_pass_us"].IsUint64());
	assert(ekfObj.HasMember("_gps_error_norm"));
assert(ekfObj["_gps_error_norm"].IsFloat() || ekfObj["_gps_error_norm"].IsBool());
	assert(ekfObj.HasMember("_min_gps_health_time_us"));
assert(ekfObj["_min_gps_health_time_us"].IsUint());
	assert(ekfObj.HasMember("_gps_checks_passed"));
assert(ekfObj["_gps_checks_passed"].IsBool());
	assert(ekfObj.HasMember("_last_gps_origin_time_us"));
assert(ekfObj["_last_gps_origin_time_us"].IsUint64());
	assert(ekfObj.HasMember("_gps_alt_ref"));
assert(ekfObj["_gps_alt_ref"].IsFloat() || ekfObj["_gps_alt_ref"].IsBool());
	assert(ekfObj.HasMember("_is_first_imu_sample"));
assert(ekfObj["_is_first_imu_sample"].IsBool());
	assert(ekfObj.HasMember("_baro_counter"));
assert(ekfObj["_baro_counter"].IsUint());
	assert(ekfObj.HasMember("_mag_counter"));
assert(ekfObj["_mag_counter"].IsUint());
	{
		assert(ekfObj.HasMember("_accel_lpf"));
		assert(ekfObj["_accel_lpf"].IsObject());
		assert(ekfObj["_accel_lpf"].HasMember("_cutoff_freq"));
		assert(ekfObj["_accel_lpf"]["_cutoff_freq"].IsFloat());
		assert(ekfObj["_accel_lpf"].HasMember("_alpha"));
		assert(ekfObj["_accel_lpf"]["_alpha"].IsFloat());
		assert(ekfObj["_accel_lpf"].HasMember("_filter_state"));
		assert(ekfObj["_accel_lpf"]["_filter_state"].IsArray());
		assert(ekfObj["_accel_lpf"]["_filter_state"].Size() == 3);
		for(int assertIndex = 0; assertIndex < 3; assertIndex++){
			assert(ekfObj["_accel_lpf"]["_filter_state"][assertIndex].IsFloat());
		}
	}
	{
		assert(ekfObj.HasMember("_gyro_lpf"));
		assert(ekfObj["_gyro_lpf"].IsObject());
		assert(ekfObj["_gyro_lpf"].HasMember("_cutoff_freq"));
		assert(ekfObj["_gyro_lpf"]["_cutoff_freq"].IsFloat());
		assert(ekfObj["_gyro_lpf"].HasMember("_alpha"));
		assert(ekfObj["_gyro_lpf"]["_alpha"].IsFloat());
		assert(ekfObj["_gyro_lpf"].HasMember("_filter_state"));
		assert(ekfObj["_gyro_lpf"]["_filter_state"].IsArray());
		assert(ekfObj["_gyro_lpf"]["_filter_state"].Size() == 3);
		for(int assertIndex = 0; assertIndex < 3; assertIndex++){
			assert(ekfObj["_gyro_lpf"]["_filter_state"][assertIndex].IsFloat());
		}
	}
	{
		assert(ekfObj.HasMember("_mag_lpf"));
		assert(ekfObj["_mag_lpf"].IsObject());
		assert(ekfObj["_mag_lpf"].HasMember("_cutoff_freq"));
		assert(ekfObj["_mag_lpf"]["_cutoff_freq"].IsFloat());
		assert(ekfObj["_mag_lpf"].HasMember("_alpha"));
		assert(ekfObj["_mag_lpf"]["_alpha"].IsFloat());
		assert(ekfObj["_mag_lpf"].HasMember("_filter_state"));
		assert(ekfObj["_mag_lpf"]["_filter_state"].IsArray());
		assert(ekfObj["_mag_lpf"]["_filter_state"].Size() == 3);
		for(int assertIndex = 0; assertIndex < 3; assertIndex++){
			assert(ekfObj["_mag_lpf"]["_filter_state"][assertIndex].IsFloat());
		}
	}
	assert(ekfObj.HasMember("_hgt_sensor_offset"));
assert(ekfObj["_hgt_sensor_offset"].IsFloat() || ekfObj["_hgt_sensor_offset"].IsBool());
	assert(ekfObj.HasMember("_baro_hgt_offset"));
assert(ekfObj["_baro_hgt_offset"].IsFloat() || ekfObj["_baro_hgt_offset"].IsBool());
	assert(ekfObj.HasMember("_baro_hgt_bias"));
assert(ekfObj["_baro_hgt_bias"].IsFloat() || ekfObj["_baro_hgt_bias"].IsBool());
	assert(ekfObj.HasMember("_baro_hgt_bias_var"));
assert(ekfObj["_baro_hgt_bias_var"].IsFloat() || ekfObj["_baro_hgt_bias_var"].IsBool());
	assert(ekfObj.HasMember("_last_on_ground_posD"));
assert(ekfObj["_last_on_ground_posD"].IsFloat() || ekfObj["_last_on_ground_posD"].IsBool());
	assert(ekfObj.HasMember("_flt_mag_align_start_time"));
assert(ekfObj["_flt_mag_align_start_time"].IsUint64());
	assert(ekfObj.HasMember("_time_last_mov_3d_mag_suitable"));
assert(ekfObj["_time_last_mov_3d_mag_suitable"].IsUint64());
	assert(ekfObj.HasMember("_saved_mag_bf_variance"));
assert(ekfObj["_saved_mag_bf_variance"].IsArray());
	assert(ekfObj.HasMember("_saved_mag_ef_ne_covmat"));
assert(ekfObj["_saved_mag_ef_ne_covmat"].IsArray());
	assert(ekfObj.HasMember("_saved_mag_ef_d_variance"));
assert(ekfObj["_saved_mag_ef_d_variance"].IsFloat() || ekfObj["_saved_mag_ef_d_variance"].IsBool());
	{
		assert(ekfObj["_gps_check_fail_status"].IsObject());
		assert(ekfObj["_gps_check_fail_status"]["flags"].IsObject());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["fix"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["hacc"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["hdrift"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["hspeed"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["nsats"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["pdop"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["sacc"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["vacc"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["vdrift"].IsBool());
		assert(ekfObj["_gps_check_fail_status"]["flags"]["vspeed"].IsBool());
	}
	assert(ekfObj.HasMember("_accel_bias_inhibit"));
assert(ekfObj["_accel_bias_inhibit"].IsArray());
	assert(ekfObj.HasMember("_accel_vec_filt"));
assert(ekfObj["_accel_vec_filt"].IsArray());
	assert(ekfObj.HasMember("_accel_magnitude_filt"));
assert(ekfObj["_accel_magnitude_filt"].IsFloat() || ekfObj["_accel_magnitude_filt"].IsBool());
	assert(ekfObj.HasMember("_ang_rate_magnitude_filt"));
assert(ekfObj["_ang_rate_magnitude_filt"].IsFloat() || ekfObj["_ang_rate_magnitude_filt"].IsBool());
	assert(ekfObj.HasMember("_prev_dvel_bias_var"));
assert(ekfObj["_prev_dvel_bias_var"].IsArray());
	assert(ekfObj.HasMember("_terrain_vpos"));
assert(ekfObj["_terrain_vpos"].IsFloat() || ekfObj["_terrain_vpos"].IsBool());
	assert(ekfObj.HasMember("_terrain_var"));
assert(ekfObj["_terrain_var"].IsFloat() || ekfObj["_terrain_var"].IsBool());
	assert(ekfObj.HasMember("_terrain_vpos_reset_counter"));
assert(ekfObj["_terrain_vpos_reset_counter"].IsUint());
	assert(ekfObj.HasMember("_time_last_hagl_fuse"));
assert(ekfObj["_time_last_hagl_fuse"].IsUint64());
	assert(ekfObj.HasMember("_hagl_valid"));
assert(ekfObj["_hagl_valid"].IsBool());
	{
		assert(ekfObj["_hagl_sensor_status"].IsObject());
		assert(ekfObj["_hagl_sensor_status"]["flags"].IsObject());
		assert(ekfObj["_hagl_sensor_status"]["flags"]["flow"].IsBool());
		assert(ekfObj["_hagl_sensor_status"]["flags"]["range_finder"].IsBool());
	}
	assert(ekfObj.HasMember("_baro_hgt_faulty"));
assert(ekfObj["_baro_hgt_faulty"].IsBool());
	assert(ekfObj.HasMember("_baro_hgt_intermittent"));
assert(ekfObj["_baro_hgt_intermittent"].IsBool());
	assert(ekfObj.HasMember("_gps_intermittent"));
assert(ekfObj["_gps_intermittent"].IsBool());
	assert(ekfObj.HasMember("_time_bad_vert_accel"));
assert(ekfObj["_time_bad_vert_accel"].IsUint64());
	assert(ekfObj.HasMember("_time_good_vert_accel"));
assert(ekfObj["_time_good_vert_accel"].IsUint64());
	assert(ekfObj.HasMember("_clip_counter"));
assert(ekfObj["_clip_counter"].IsUint());
	assert(ekfObj.HasMember("_is_range_aid_suitable"));
assert(ekfObj["_is_range_aid_suitable"].IsBool());
	assert(ekfObj.HasMember("_height_rate_lpf"));
assert(ekfObj["_height_rate_lpf"].IsFloat() || ekfObj["_height_rate_lpf"].IsBool());
			assert(ekfObj.HasMember("_ekfgsf_yaw_reset_time"));
assert(ekfObj["_ekfgsf_yaw_reset_time"].IsInt64());
	assert(ekfObj.HasMember("_ekfgsf_yaw_reset_count"));
assert(ekfObj["_ekfgsf_yaw_reset_count"].IsUint());

}
void Ekf::ekfLoadFromJson(rapidjson::Value & ekfObj){
	rapidjson::Value & yawObj = ekfObj["_yawEstimator"];
	_yawEstimator.fromJson(yawObj);
	rapidjson::Value & baroObj = ekfObj["_baro_b_est"];
	_baro_b_est.fromJson(baroObj);
{
}
{
}
{
}
{
	for(int i = 0; i < 3; i++){
		_ang_rate_delayed_raw(i) = ekfObj["_ang_rate_delayed_raw"][i].GetFloat();
	}
}
{
	rapidjson::Value& structObj = ekfObj["_state"];
		for(int i = 0; i < 4; i++){
			_state.quat_nominal(i) = structObj["quat_nominal"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_state.vel(i) = structObj["vel"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_state.pos(i) = structObj["pos"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_state.delta_ang_bias(i) = structObj["delta_ang_bias"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_state.delta_vel_bias(i) = structObj["delta_vel_bias"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_state.mag_I(i) = structObj["mag_I"][i].GetFloat();
		}
		for(int i = 0; i < 3; i++){
			_state.mag_B(i) = structObj["mag_B"][i].GetFloat();
		}
		for(int i = 0; i < 2; i++){
			_state.wind_vel(i) = structObj["wind_vel"][i].GetFloat();
		}
}
{
		_filter_initialised = ekfObj["_filter_initialised"].GetBool();
}
{
		_fuse_hpos_as_odom = ekfObj["_fuse_hpos_as_odom"].GetBool();
}
{
	for(int i = 0; i < 2; i++){
		_hpos_pred_prev(i) = ekfObj["_hpos_pred_prev"][i].GetFloat();
	}
}
{
		_hpos_prev_available = ekfObj["_hpos_prev_available"].GetBool();
}
{
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			_R_ev_to_ekf(i, j) = ekfObj["_R_ev_to_ekf"][i*3 + j].GetFloat();
		}
	}
}
{
		_inhibit_ev_yaw_use = ekfObj["_inhibit_ev_yaw_use"].GetBool();
}
{
		_gps_data_ready = ekfObj["_gps_data_ready"].GetBool();
}
{
		_baro_data_ready = ekfObj["_baro_data_ready"].GetBool();
}
{
		_flow_data_ready = ekfObj["_flow_data_ready"].GetBool();
}
{
		_ev_data_ready = ekfObj["_ev_data_ready"].GetBool();
}
{
		_tas_data_ready = ekfObj["_tas_data_ready"].GetBool();
}
{
		_flow_for_terrain_data_ready = ekfObj["_flow_for_terrain_data_ready"].GetBool();
}
{
		_time_prev_gps_us = ekfObj["_time_prev_gps_us"].GetUint64();
}
{
		_time_last_aiding = ekfObj["_time_last_aiding"].GetUint64();
}
{
		_using_synthetic_position = ekfObj["_using_synthetic_position"].GetBool();
}
{
		_time_last_hor_pos_fuse = ekfObj["_time_last_hor_pos_fuse"].GetUint64();
}
{
		_time_last_hgt_fuse = ekfObj["_time_last_hgt_fuse"].GetUint64();
}
{
		_time_last_hor_vel_fuse = ekfObj["_time_last_hor_vel_fuse"].GetUint64();
}
{
		_time_last_ver_vel_fuse = ekfObj["_time_last_ver_vel_fuse"].GetUint64();
}
{
		_time_last_of_fuse = ekfObj["_time_last_of_fuse"].GetUint64();
}
{
		_time_last_flow_terrain_fuse = ekfObj["_time_last_flow_terrain_fuse"].GetUint64();
}
{
		_time_last_arsp_fuse = ekfObj["_time_last_arsp_fuse"].GetUint64();
}
{
		_time_last_beta_fuse = ekfObj["_time_last_beta_fuse"].GetUint64();
}
{
		_time_last_fake_pos_fuse = ekfObj["_time_last_fake_pos_fuse"].GetUint64();
}
{
		_time_last_zero_velocity_fuse = ekfObj["_time_last_zero_velocity_fuse"].GetUint64();
}
{
		_time_last_gps_yaw_fuse = ekfObj["_time_last_gps_yaw_fuse"].GetUint64();
}
{
		_time_last_gps_yaw_data = ekfObj["_time_last_gps_yaw_data"].GetUint64();
}
{
		_time_last_healthy_rng_data = ekfObj["_time_last_healthy_rng_data"].GetUint64();
}
{
		_nb_gps_yaw_reset_available = ekfObj["_nb_gps_yaw_reset_available"].GetUint();
}
{
	for(int i = 0; i < 2; i++){
		_last_known_posNE(i) = ekfObj["_last_known_posNE"][i].GetFloat();
	}
}
{
		_time_acc_bias_check = ekfObj["_time_acc_bias_check"].GetUint64();
}
{
		_delta_time_baro_us = ekfObj["_delta_time_baro_us"].GetUint64();
}
{
	for(int i = 0; i < 3; i++){
		_earth_rate_NED(i) = ekfObj["_earth_rate_NED"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			_R_to_earth(i, j) = ekfObj["_R_to_earth"][i*3 + j].GetFloat();
		}
	}
}
{
	for(int i = 0; i < 2; i++){
		_accel_lpf_NE(i) = ekfObj["_accel_lpf_NE"][i].GetFloat();
	}
}
{
	if (ekfObj["_yaw_delta_ef"].IsBool()){
		_yaw_delta_ef = NAN;
	}else{
		_yaw_delta_ef = ekfObj["_yaw_delta_ef"].GetFloat();
	}
}
{
	if (ekfObj["_yaw_rate_lpf_ef"].IsBool()){
		_yaw_rate_lpf_ef = NAN;
	}else{
		_yaw_rate_lpf_ef = ekfObj["_yaw_rate_lpf_ef"].GetFloat();
	}
}
{
		_mag_bias_observable = ekfObj["_mag_bias_observable"].GetBool();
}
{
		_yaw_angle_observable = ekfObj["_yaw_angle_observable"].GetBool();
}
{
		_time_yaw_started = ekfObj["_time_yaw_started"].GetUint64();
}
{
		_num_bad_flight_yaw_events = ekfObj["_num_bad_flight_yaw_events"].GetUint();
}
{
		_mag_use_not_inhibit_us = ekfObj["_mag_use_not_inhibit_us"].GetUint64();
}
{
	if (ekfObj["_last_static_yaw"].IsBool()){
		_last_static_yaw = NAN;
	}else{
		_last_static_yaw = ekfObj["_last_static_yaw"].GetFloat();
	}
}
{
		_mag_inhibit_yaw_reset_req = ekfObj["_mag_inhibit_yaw_reset_req"].GetBool();
}
{
		_mag_yaw_reset_req = ekfObj["_mag_yaw_reset_req"].GetBool();
}
{
		_mag_decl_cov_reset = ekfObj["_mag_decl_cov_reset"].GetBool();
}
{
		_synthetic_mag_z_active = ekfObj["_synthetic_mag_z_active"].GetBool();
}
{
		_non_mag_yaw_aiding_running_prev = ekfObj["_non_mag_yaw_aiding_running_prev"].GetBool();
}
{
		_is_yaw_fusion_inhibited = ekfObj["_is_yaw_fusion_inhibited"].GetBool();
}
{
	for(int i = 0; i < 24; i++){
		for(int j = 0; j < 24; j++){
			P(i, j) = ekfObj["P"][i*24 + j].GetFloat();
		}
	}
}
{
	for(int i = 0; i < 3; i++){
		_delta_vel_bias_var_accum(i) = ekfObj["_delta_vel_bias_var_accum"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_delta_angle_bias_var_accum(i) = ekfObj["_delta_angle_bias_var_accum"][i].GetFloat();
	}
}
{
	if (ekfObj["_vert_pos_innov_ratio"].IsBool()){
		_vert_pos_innov_ratio = NAN;
	}else{
		_vert_pos_innov_ratio = ekfObj["_vert_pos_innov_ratio"].GetFloat();
	}
}
{
		_vert_pos_fuse_attempt_time_us = ekfObj["_vert_pos_fuse_attempt_time_us"].GetUint64();
}
{
	if (ekfObj["_vert_vel_innov_ratio"].IsBool()){
		_vert_vel_innov_ratio = NAN;
	}else{
		_vert_vel_innov_ratio = ekfObj["_vert_vel_innov_ratio"].GetFloat();
	}
}
{
		_vert_vel_fuse_time_us = ekfObj["_vert_vel_fuse_time_us"].GetUint64();
}
{
	for(int i = 0; i < 3; i++){
		_gps_vel_innov(i) = ekfObj["_gps_vel_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_gps_vel_innov_var(i) = ekfObj["_gps_vel_innov_var"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_gps_pos_innov(i) = ekfObj["_gps_pos_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_gps_pos_innov_var(i) = ekfObj["_gps_pos_innov_var"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_ev_vel_innov(i) = ekfObj["_ev_vel_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_ev_vel_innov_var(i) = ekfObj["_ev_vel_innov_var"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_ev_pos_innov(i) = ekfObj["_ev_pos_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_ev_pos_innov_var(i) = ekfObj["_ev_pos_innov_var"][i].GetFloat();
	}
}
{
	if (ekfObj["_baro_hgt_innov"].IsBool()){
		_baro_hgt_innov = NAN;
	}else{
		_baro_hgt_innov = ekfObj["_baro_hgt_innov"].GetFloat();
	}
}
{
	if (ekfObj["_baro_hgt_innov_var"].IsBool()){
		_baro_hgt_innov_var = NAN;
	}else{
		_baro_hgt_innov_var = ekfObj["_baro_hgt_innov_var"].GetFloat();
	}
}
{
	if (ekfObj["_rng_hgt_innov"].IsBool()){
		_rng_hgt_innov = NAN;
	}else{
		_rng_hgt_innov = ekfObj["_rng_hgt_innov"].GetFloat();
	}
}
{
	if (ekfObj["_rng_hgt_innov_var"].IsBool()){
		_rng_hgt_innov_var = NAN;
	}else{
		_rng_hgt_innov_var = ekfObj["_rng_hgt_innov_var"].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_aux_vel_innov(i) = ekfObj["_aux_vel_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_aux_vel_innov_var(i) = ekfObj["_aux_vel_innov_var"][i].GetFloat();
	}
}
{
	if (ekfObj["_heading_innov"].IsBool()){
		_heading_innov = NAN;
	}else{
		_heading_innov = ekfObj["_heading_innov"].GetFloat();
	}
}
{
	if (ekfObj["_heading_innov_var"].IsBool()){
		_heading_innov_var = NAN;
	}else{
		_heading_innov_var = ekfObj["_heading_innov_var"].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_mag_innov(i) = ekfObj["_mag_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_mag_innov_var(i) = ekfObj["_mag_innov_var"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_drag_innov(i) = ekfObj["_drag_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_drag_innov_var(i) = ekfObj["_drag_innov_var"][i].GetFloat();
	}
}
{
	if (ekfObj["_airspeed_innov"].IsBool()){
		_airspeed_innov = NAN;
	}else{
		_airspeed_innov = ekfObj["_airspeed_innov"].GetFloat();
	}
}
{
	if (ekfObj["_airspeed_innov_var"].IsBool()){
		_airspeed_innov_var = NAN;
	}else{
		_airspeed_innov_var = ekfObj["_airspeed_innov_var"].GetFloat();
	}
}
{
	if (ekfObj["_beta_innov"].IsBool()){
		_beta_innov = NAN;
	}else{
		_beta_innov = ekfObj["_beta_innov"].GetFloat();
	}
}
{
	if (ekfObj["_beta_innov_var"].IsBool()){
		_beta_innov_var = NAN;
	}else{
		_beta_innov_var = ekfObj["_beta_innov_var"].GetFloat();
	}
}
{
	if (ekfObj["_hagl_innov"].IsBool()){
		_hagl_innov = NAN;
	}else{
		_hagl_innov = ekfObj["_hagl_innov"].GetFloat();
	}
}
{
	if (ekfObj["_hagl_innov_var"].IsBool()){
		_hagl_innov_var = NAN;
	}else{
		_hagl_innov_var = ekfObj["_hagl_innov_var"].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_flow_innov(i) = ekfObj["_flow_innov"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_flow_innov_var(i) = ekfObj["_flow_innov_var"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_flow_gyro_bias(i) = ekfObj["_flow_gyro_bias"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_flow_vel_body(i) = ekfObj["_flow_vel_body"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_flow_vel_ne(i) = ekfObj["_flow_vel_ne"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_imu_del_ang_of(i) = ekfObj["_imu_del_ang_of"][i].GetFloat();
	}
}
{
	if (ekfObj["_delta_time_of"].IsBool()){
		_delta_time_of = NAN;
	}else{
		_delta_time_of = ekfObj["_delta_time_of"].GetFloat();
	}
}
{
		_time_bad_motion_us = ekfObj["_time_bad_motion_us"].GetUint64();
}
{
		_time_good_motion_us = ekfObj["_time_good_motion_us"].GetUint64();
}
{
		_inhibit_flow_use = ekfObj["_inhibit_flow_use"].GetBool();
}
{
	for(int i = 0; i < 2; i++){
		_flow_compensated_XY_rad(i) = ekfObj["_flow_compensated_XY_rad"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_delta_angle_corr(i) = ekfObj["_delta_angle_corr"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_vel_err_integ(i) = ekfObj["_vel_err_integ"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_pos_err_integ(i) = ekfObj["_pos_err_integ"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_output_tracking_error(i) = ekfObj["_output_tracking_error"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_gps_pos_deriv_filt(i) = ekfObj["_gps_pos_deriv_filt"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		_gps_velNE_filt(i) = ekfObj["_gps_velNE_filt"][i].GetFloat();
	}
}
{
	if (ekfObj["_gps_velD_diff_filt"].IsBool()){
		_gps_velD_diff_filt = NAN;
	}else{
		_gps_velD_diff_filt = ekfObj["_gps_velD_diff_filt"].GetFloat();
	}
}
{
		_last_gps_fail_us = ekfObj["_last_gps_fail_us"].GetUint64();
}
{
		_last_gps_pass_us = ekfObj["_last_gps_pass_us"].GetUint64();
}
{
	if (ekfObj["_gps_error_norm"].IsBool()){
		_gps_error_norm = NAN;
	}else{
		_gps_error_norm = ekfObj["_gps_error_norm"].GetFloat();
	}
}
{
		_min_gps_health_time_us = ekfObj["_min_gps_health_time_us"].GetUint();
}
{
		_gps_checks_passed = ekfObj["_gps_checks_passed"].GetBool();
}
{
		_last_gps_origin_time_us = ekfObj["_last_gps_origin_time_us"].GetUint64();
}
{
	if (ekfObj["_gps_alt_ref"].IsBool()){
		_gps_alt_ref = NAN;
	}else{
		_gps_alt_ref = ekfObj["_gps_alt_ref"].GetFloat();
	}
}
{
		_is_first_imu_sample = ekfObj["_is_first_imu_sample"].GetBool();
}
{
		_baro_counter = ekfObj["_baro_counter"].GetUint();
}
{
		_mag_counter = ekfObj["_mag_counter"].GetUint();
}
	{
		auto & afJson = ekfObj["_accel_lpf"];
		_accel_lpf.setCutoff(afJson["_cutoff_freq"].GetFloat());
		_accel_lpf.setAlpha(afJson["_alpha"].GetFloat());
		Vector3f tmpVec;
		for(int afIndex = 0; afIndex < 3; afIndex++){
			tmpVec(afIndex) = afJson["_filter_state"][afIndex].GetFloat();
		}
		_accel_lpf.setState(tmpVec);
	}
	{
		auto & afJson = ekfObj["_gyro_lpf"];
		_gyro_lpf.setCutoff(afJson["_cutoff_freq"].GetFloat());
		_gyro_lpf.setAlpha(afJson["_alpha"].GetFloat());
		Vector3f tmpVec;
		for(int afIndex = 0; afIndex < 3; afIndex++){
			tmpVec(afIndex) = afJson["_filter_state"][afIndex].GetFloat();
		}
		_gyro_lpf.setState(tmpVec);
	}
	{
		auto & afJson = ekfObj["_mag_lpf"];
		_mag_lpf.setCutoff(afJson["_cutoff_freq"].GetFloat());
		_mag_lpf.setAlpha(afJson["_alpha"].GetFloat());
		Vector3f tmpVec;
		for(int afIndex = 0; afIndex < 3; afIndex++){
			tmpVec(afIndex) = afJson["_filter_state"][afIndex].GetFloat();
		}
		_mag_lpf.setState(tmpVec);
	}
{
	if (ekfObj["_hgt_sensor_offset"].IsBool()){
		_hgt_sensor_offset = NAN;
	}else{
		_hgt_sensor_offset = ekfObj["_hgt_sensor_offset"].GetFloat();
	}
}
{
	if (ekfObj["_baro_hgt_offset"].IsBool()){
		_baro_hgt_offset = NAN;
	}else{
		_baro_hgt_offset = ekfObj["_baro_hgt_offset"].GetFloat();
	}
}
{
	if (ekfObj["_baro_hgt_bias"].IsBool()){
		_baro_hgt_bias = NAN;
	}else{
		_baro_hgt_bias = ekfObj["_baro_hgt_bias"].GetFloat();
	}
}
{
	if (ekfObj["_baro_hgt_bias_var"].IsBool()){
		_baro_hgt_bias_var = NAN;
	}else{
		_baro_hgt_bias_var = ekfObj["_baro_hgt_bias_var"].GetFloat();
	}
}
{
	if (ekfObj["_last_on_ground_posD"].IsBool()){
		_last_on_ground_posD = NAN;
	}else{
		_last_on_ground_posD = ekfObj["_last_on_ground_posD"].GetFloat();
	}
}
{
		_flt_mag_align_start_time = ekfObj["_flt_mag_align_start_time"].GetUint64();
}
{
		_time_last_mov_3d_mag_suitable = ekfObj["_time_last_mov_3d_mag_suitable"].GetUint64();
}
{
	for(int i = 0; i < 3; i++){
		_saved_mag_bf_variance(i) = ekfObj["_saved_mag_bf_variance"][i].GetFloat();
	}
}
{
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			_saved_mag_ef_ne_covmat(i, j) = ekfObj["_saved_mag_ef_ne_covmat"][i*2 + j].GetFloat();
		}
	}
}
{
	if (ekfObj["_saved_mag_ef_d_variance"].IsBool()){
		_saved_mag_ef_d_variance = NAN;
	}else{
		_saved_mag_ef_d_variance = ekfObj["_saved_mag_ef_d_variance"].GetFloat();
	}
}
	{
		rapidjson::Value& innerJson = ekfObj["_gps_check_fail_status"]["flags"];
		_gps_check_fail_status.flags.fix = innerJson["fix"].GetBool();
		_gps_check_fail_status.flags.hacc = innerJson["hacc"].GetBool();
		_gps_check_fail_status.flags.hdrift = innerJson["hdrift"].GetBool();
		_gps_check_fail_status.flags.hspeed = innerJson["hspeed"].GetBool();
		_gps_check_fail_status.flags.nsats = innerJson["nsats"].GetBool();
		_gps_check_fail_status.flags.pdop = innerJson["pdop"].GetBool();
		_gps_check_fail_status.flags.sacc = innerJson["sacc"].GetBool();
		_gps_check_fail_status.flags.vacc = innerJson["vacc"].GetBool();
		_gps_check_fail_status.flags.vdrift = innerJson["vdrift"].GetBool();
		_gps_check_fail_status.flags.vspeed = innerJson["vspeed"].GetBool();
}{
	for(int i = 0; i < 3; i++){
		_accel_bias_inhibit[i] = ekfObj["_accel_bias_inhibit"][i].GetBool();
	}
}
{
	for(int i = 0; i < 3; i++){
		_accel_vec_filt(i) = ekfObj["_accel_vec_filt"][i].GetFloat();
	}
}
{
	if (ekfObj["_accel_magnitude_filt"].IsBool()){
		_accel_magnitude_filt = NAN;
	}else{
		_accel_magnitude_filt = ekfObj["_accel_magnitude_filt"].GetFloat();
	}
}
{
	if (ekfObj["_ang_rate_magnitude_filt"].IsBool()){
		_ang_rate_magnitude_filt = NAN;
	}else{
		_ang_rate_magnitude_filt = ekfObj["_ang_rate_magnitude_filt"].GetFloat();
	}
}
{
	for(int i = 0; i < 3; i++){
		_prev_dvel_bias_var(i) = ekfObj["_prev_dvel_bias_var"][i].GetFloat();
	}
}
{
	if (ekfObj["_terrain_vpos"].IsBool()){
		_terrain_vpos = NAN;
	}else{
		_terrain_vpos = ekfObj["_terrain_vpos"].GetFloat();
	}
}
{
	if (ekfObj["_terrain_var"].IsBool()){
		_terrain_var = NAN;
	}else{
		_terrain_var = ekfObj["_terrain_var"].GetFloat();
	}
}
{
		_terrain_vpos_reset_counter = ekfObj["_terrain_vpos_reset_counter"].GetUint();
}
{
		_time_last_hagl_fuse = ekfObj["_time_last_hagl_fuse"].GetUint64();
}
{
		_hagl_valid = ekfObj["_hagl_valid"].GetBool();
}
	{
		rapidjson::Value& innerJson = ekfObj["_hagl_sensor_status"]["flags"];
		_hagl_sensor_status.flags.flow = innerJson["flow"].GetBool();
		_hagl_sensor_status.flags.range_finder = innerJson["range_finder"].GetBool();
}{
		_baro_hgt_faulty = ekfObj["_baro_hgt_faulty"].GetBool();
}
{
		_baro_hgt_intermittent = ekfObj["_baro_hgt_intermittent"].GetBool();
}
{
		_gps_intermittent = ekfObj["_gps_intermittent"].GetBool();
}
{
		_time_bad_vert_accel = ekfObj["_time_bad_vert_accel"].GetUint64();
}
{
		_time_good_vert_accel = ekfObj["_time_good_vert_accel"].GetUint64();
}
{
		_clip_counter = ekfObj["_clip_counter"].GetUint();
}
{
		_is_range_aid_suitable = ekfObj["_is_range_aid_suitable"].GetBool();
}
{
	if (ekfObj["_height_rate_lpf"].IsBool()){
		_height_rate_lpf = NAN;
	}else{
		_height_rate_lpf = ekfObj["_height_rate_lpf"].GetFloat();
	}
}
{
}
{
}
{
		_ekfgsf_yaw_reset_time = ekfObj["_ekfgsf_yaw_reset_time"].GetInt64();
}
{
		_ekfgsf_yaw_reset_count = ekfObj["_ekfgsf_yaw_reset_count"].GetUint();
}

}
