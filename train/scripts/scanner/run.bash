#/bin/bash

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

python gen_structs.py

python parse_var.py

cp  $SCRIPT_DIR/output/ei_addon.cpp $SCRIPT_DIR/../lib/ecl_ekf/
cp  $SCRIPT_DIR/output/ekf_addon.cpp $SCRIPT_DIR/../lib/ecl_ekf/
#cp  $SCRIPT_DIR/output/mod_addon.cpp $SCRIPT_DIR/../lib/ecl_ekf/