# Pre-Processing Scripts
Scripts in this directory converts the json logs to a dataset.

log -> parsed_log  -> dataset

# Log
Log is the exfiltrated snapshot data.
The fields in the snapshots are encoded using `nameToId.json`.
Encoding is necessary to compress the data to prevent overloading the network sockets.

## Lookup tables
`gen_index.py` is used to generate the following lookup tables:
- `nameToIndex.json`: Used to find which name corresponds to which field in the vector
  - For a given name in a log that hold an array, each elements of the array is assigned a unique index
  - e.g., `log[field_name] := [v_1, v_2, ..., v_n]` -> `nameToIndex[field_name] := [i_1, i_2, ..., i_n]`
    - `v_1, ..., v_n` are values of `field_name`
    - `i_1, ..., i_n` are the indices in the outputted vector that hold the values `v_1, ..., v_n` respectively
- `indexToname.json`: The inverse of `nameToIndex.json`
Running the `gen_index.py` requires a single snapshot from log file with the following encoding tables:
- `idToName.json`: Used to convert encoded field name to human readable name
- `nameToId.json`: The inverse of `idToName.json`

# Parsed Log
Parsed log is the vectorization of the json logs.
`to_vec.py` is reponsible for converting the json logs to numpy arrays.
The saved numpy file is in following format:
- `f`: 
  - 0: vectorized `pref`
  - 1: vectorized `postf`
- `h`: (i.e., the target function)
  - 0: vectorized `postf`
  - 1: vectorized `posth`
