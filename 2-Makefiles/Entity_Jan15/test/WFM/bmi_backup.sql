BEGIN TRANSACTION;
CREATE TABLE bf_t (pkey INTEGER PRIMARY KEY, bf_val TEXT, log_time TEXT);
CREATE TABLE bmi_t (pkey INTEGER PRIMARY KEY, weight TEXT, bmi TEXT, height TEXT, log_time TEXT);
CREATE TABLE bp_t (pkey INTEGER PRIMARY KEY, sbp_val TEXT, dbp_val TEXT, pr_val TEXT, log_time TEXT);
CREATE TABLE co_t (pkey INTEGER PRIMARY KEY, co_val TEXT, log_time TEXT);
COMMIT;
