MODULES = external
EXTENSION = external
DATA = external--1.0.sql
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)

LDFLAGS = -lgsl -lgslcblas -lm
