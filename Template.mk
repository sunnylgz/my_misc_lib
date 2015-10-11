#=============================================================================
#           target
#=============================================================================
libs:=$(PATH_LIBS)/lib$(LIB_NAME).a
app:=test_$(LIB_NAME).exe

#=============================================================================
#           .PHONY
#=============================================================================
all: clean_logs $(PATH_LOGS) $(PATH_LIBS) $(PATH_APP) $(libs) $(app)

clean_logs:
	-rm $(LIBS_LOG) $(APP_LOG)

clean:clean_logs
	-rm $(LIBS_C) $(APP_C) $(libs) $(app)

$(PATH_LOGS):
	-mkdir $(PATH_LOGS)

$(PATH_LIBS):
	-mkdir $(PATH_LIBS)

$(PATH_APP):
	-mkdir $(PATH_APP)

$(LIBS_C):%.o:%.c
	-$(CC) -c $< -o $@ $(CFLAGS) $(OPT_INCLUDE) 1>>$(LIBS_LOG) 2>>$(LIBS_LOG)
	@if [ -e $@ ]; then echo [success] C compile [$<] to [$@] >>$(LIBS_LOG); else echo [failed] C compile [$<] to [$@] >>$(LIBS_LOG); fi

$(APP_C):%.o:%.c
	-$(CC) -c $< -o $@ $(CFLAGS) $(OPT_INCLUDE) 1>>$(APP_LOG) 2>>$(APP_LOG)
	@if [ -e $@ ]; then echo [success] C compile [$<] to [$@] >>$(APP_LOG); else echo [failed] C compile [$<] to [$@] >>$(APP_LOG); fi

$(libs):$(LIBS_C)
	-$(AR) $(ARFLAGS) -r $@ $(LIBS_C) $(USR_LIBS) 1>>$(LIBS_LOG) 2>>$(LIBS_LOG)
	@if [ -e $@ ]; then echo [success] AR [$@] 1>> $(LIBS_LOG) 2>>$(LIBS_LOG); else echo [failed] AR [$@] 1>> $(LIBS_LOG) 2>>$(LIBS_LOG); fi

$(app):$(libs) $(APP_C)
	-$(LD) -o $@ $(libs) $(APP_C) $(USR_LIBS) $(LNFLAGS) 1>>$(APP_LOG) 2>>$(APP_LOG)
	@if [ -e $@ ]; then echo [success] Link [$@] 1>>$(APP_LOG) 2>>$(APP_LOG); else echo [failed] Link [$@] 1>>$(APP_LOG) 2>>$(APP_LOG); fi
