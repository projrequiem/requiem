#include "baro_bias_estimator.hpp"
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/filereadstream.h>
void BaroBiasEstimator::toJson(rapidjson::Value & ekfObj, rapidjson::Document::AllocatorType & allocator){
{
}
{
	if (isnan(_state)){
		ekfObj.AddMember("_state", false, allocator);
	}else{
		ekfObj.AddMember("_state", _state, allocator);
	}
}
{
	if (isnan(_state_max)){
		ekfObj.AddMember("_state_max", false, allocator);
	}else{
		ekfObj.AddMember("_state_max", _state_max, allocator);
	}
}
{
	if (isnan(_state_drift_rate)){
		ekfObj.AddMember("_state_drift_rate", false, allocator);
	}else{
		ekfObj.AddMember("_state_drift_rate", _state_drift_rate, allocator);
	}
}
{
	if (isnan(_dt)){
		ekfObj.AddMember("_dt", false, allocator);
	}else{
		ekfObj.AddMember("_dt", _dt, allocator);
	}
}
{
	if (isnan(_gate_size)){
		ekfObj.AddMember("_gate_size", false, allocator);
	}else{
		ekfObj.AddMember("_gate_size", _gate_size, allocator);
	}
}
{
	if (isnan(_state_var)){
		ekfObj.AddMember("_state_var", false, allocator);
	}else{
		ekfObj.AddMember("_state_var", _state_var, allocator);
	}
}
{
	if (isnan(_process_var)){
		ekfObj.AddMember("_process_var", false, allocator);
	}else{
		ekfObj.AddMember("_process_var", _process_var, allocator);
	}
}
{
	if (isnan(_state_var_max)){
		ekfObj.AddMember("_state_var_max", false, allocator);
	}else{
		ekfObj.AddMember("_state_var_max", _state_var_max, allocator);
	}
}
	{
		rapidjson::Value floatAF(rapidjson::kObjectType);
		floatAF.AddMember("_cutoff_freq", _signed_innov_test_ratio_lpf.getCutoffFreq(), allocator);
		floatAF.AddMember("_alpha", _signed_innov_test_ratio_lpf.getAlpha(), allocator);
		if (isnan(_signed_innov_test_ratio_lpf.getState())){
			floatAF.AddMember("_filter_state", false, allocator);
		}else{
			floatAF.AddMember("_filter_state", _signed_innov_test_ratio_lpf.getState(), allocator);
		}
		ekfObj.AddMember("_signed_innov_test_ratio_lpf", floatAF, allocator);
	}
	{
		rapidjson::Value structObj(rapidjson::kObjectType);
		structObj.SetObject();
		if (isnan(_status.bias)){
			structObj.AddMember("bias", false, allocator);
		}else{
			structObj.AddMember("bias", _status.bias, allocator);
		}
		if (isnan(_status.bias_var)){
			structObj.AddMember("bias_var", false, allocator);
		}else{
			structObj.AddMember("bias_var", _status.bias_var, allocator);
		}
		if (isnan(_status.innov)){
			structObj.AddMember("innov", false, allocator);
		}else{
			structObj.AddMember("innov", _status.innov, allocator);
		}
		if (isnan(_status.innov_var)){
			structObj.AddMember("innov_var", false, allocator);
		}else{
			structObj.AddMember("innov_var", _status.innov_var, allocator);
		}
		if (isnan(_status.innov_test_ratio)){
			structObj.AddMember("innov_test_ratio", false, allocator);
		}else{
			structObj.AddMember("innov_test_ratio", _status.innov_test_ratio, allocator);
		}
		ekfObj.AddMember("_status", structObj, allocator);
	}
{
}
{
}

}
void BaroBiasEstimator::checkJson(rapidjson::Value & ekfObj){
		assert(ekfObj.HasMember("_state"));
assert(ekfObj["_state"].IsFloat() || ekfObj["_state"].IsBool());
	assert(ekfObj.HasMember("_state_max"));
assert(ekfObj["_state_max"].IsFloat() || ekfObj["_state_max"].IsBool());
	assert(ekfObj.HasMember("_state_drift_rate"));
assert(ekfObj["_state_drift_rate"].IsFloat() || ekfObj["_state_drift_rate"].IsBool());
	assert(ekfObj.HasMember("_dt"));
assert(ekfObj["_dt"].IsFloat() || ekfObj["_dt"].IsBool());
	assert(ekfObj.HasMember("_gate_size"));
assert(ekfObj["_gate_size"].IsFloat() || ekfObj["_gate_size"].IsBool());
	assert(ekfObj.HasMember("_state_var"));
assert(ekfObj["_state_var"].IsFloat() || ekfObj["_state_var"].IsBool());
	assert(ekfObj.HasMember("_process_var"));
assert(ekfObj["_process_var"].IsFloat() || ekfObj["_process_var"].IsBool());
	assert(ekfObj.HasMember("_state_var_max"));
assert(ekfObj["_state_var_max"].IsFloat() || ekfObj["_state_var_max"].IsBool());
	{
		assert(ekfObj.HasMember("_signed_innov_test_ratio_lpf"));
		assert(ekfObj["_signed_innov_test_ratio_lpf"].IsObject());
		assert(ekfObj["_signed_innov_test_ratio_lpf"].HasMember("_cutoff_freq"));
		assert(ekfObj["_signed_innov_test_ratio_lpf"]["_cutoff_freq"].IsFloat());
		assert(ekfObj["_signed_innov_test_ratio_lpf"].HasMember("_alpha"));
		assert(ekfObj["_signed_innov_test_ratio_lpf"]["_alpha"].IsFloat());
		assert(ekfObj["_signed_innov_test_ratio_lpf"].HasMember("_filter_state"));
		assert(ekfObj["_signed_innov_test_ratio_lpf"]["_filter_state"].IsFloat());
	}
{
	assert(ekfObj["_status"].IsObject());
	assert(ekfObj["_status"]["bias"].IsFloat() || ekfObj["_status"]["bias"].IsBool());
	assert(ekfObj["_status"]["bias_var"].IsFloat() || ekfObj["_status"]["bias_var"].IsBool());
	assert(ekfObj["_status"]["innov"].IsFloat() || ekfObj["_status"]["innov"].IsBool());
	assert(ekfObj["_status"]["innov_var"].IsFloat() || ekfObj["_status"]["innov_var"].IsBool());
	assert(ekfObj["_status"]["innov_test_ratio"].IsFloat() || ekfObj["_status"]["innov_test_ratio"].IsBool());
}
		
}
void BaroBiasEstimator::fromJson(rapidjson::Value & ekfObj){
{
}
{
	if (ekfObj["_state"].IsBool()){
		_state = NAN;
	}else{
		_state = ekfObj["_state"].GetFloat();
	}
}
{
	if (ekfObj["_state_max"].IsBool()){
		_state_max = NAN;
	}else{
		_state_max = ekfObj["_state_max"].GetFloat();
	}
}
{
	if (ekfObj["_state_drift_rate"].IsBool()){
		_state_drift_rate = NAN;
	}else{
		_state_drift_rate = ekfObj["_state_drift_rate"].GetFloat();
	}
}
{
	if (ekfObj["_dt"].IsBool()){
		_dt = NAN;
	}else{
		_dt = ekfObj["_dt"].GetFloat();
	}
}
{
	if (ekfObj["_gate_size"].IsBool()){
		_gate_size = NAN;
	}else{
		_gate_size = ekfObj["_gate_size"].GetFloat();
	}
}
{
	if (ekfObj["_state_var"].IsBool()){
		_state_var = NAN;
	}else{
		_state_var = ekfObj["_state_var"].GetFloat();
	}
}
{
	if (ekfObj["_process_var"].IsBool()){
		_process_var = NAN;
	}else{
		_process_var = ekfObj["_process_var"].GetFloat();
	}
}
{
	if (ekfObj["_state_var_max"].IsBool()){
		_state_var_max = NAN;
	}else{
		_state_var_max = ekfObj["_state_var_max"].GetFloat();
	}
}
	{
		auto & afJson = ekfObj["_signed_innov_test_ratio_lpf"];
		_signed_innov_test_ratio_lpf.setCutoff(afJson["_cutoff_freq"].GetFloat());
		_signed_innov_test_ratio_lpf.setAlpha(afJson["_alpha"].GetFloat());
		_signed_innov_test_ratio_lpf.setState(afJson["_filter_state"].GetFloat());
	}
{
	rapidjson::Value& structObj = ekfObj["_status"];
		if (structObj["bias"].IsBool()){
			_status.bias = NAN;
		}else{
			_status.bias = structObj["bias"].GetFloat();
		}
		if (structObj["bias_var"].IsBool()){
			_status.bias_var = NAN;
		}else{
			_status.bias_var = structObj["bias_var"].GetFloat();
		}
		if (structObj["innov"].IsBool()){
			_status.innov = NAN;
		}else{
			_status.innov = structObj["innov"].GetFloat();
		}
		if (structObj["innov_var"].IsBool()){
			_status.innov_var = NAN;
		}else{
			_status.innov_var = structObj["innov_var"].GetFloat();
		}
		if (structObj["innov_test_ratio"].IsBool()){
			_status.innov_test_ratio = NAN;
		}else{
			_status.innov_test_ratio = structObj["innov_test_ratio"].GetFloat();
		}
}
{
}
{
}

}
