#/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
if [[ -z "${PX4_DIR}" ]]; then
  EKF_DIR="${SCRIPT_DIR}/../../PX4-Autopilot/src/modules/ekf2/"
else
  EKF_DIR="${PX4_DIR}/src/modules/ekf2/"
fi

python gen_structs.py

python parse_var.py

cp  $SCRIPT_DIR/output/ei_addon.cpp "${EKF_DIR}/EKF/"
cp  $SCRIPT_DIR/output/ekf_addon.cpp "${EKF_DIR}/EKF/"
cp  $SCRIPT_DIR/output/mod_addon.cpp $EKF_DIR