#-- start of make_header -----------------

#====================================
#  Library QualityCheckAlg
#
#   Generated Fri Sep 24 09:40:18 2021  by xiaogy
#
#====================================

include ${CMTROOT}/src/Makefile.core

ifdef tag
CMTEXTRATAGS = $(tag)
else
tag       = $(CMTCONFIG)
endif

cmt_QualityCheckAlg_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_QualityCheckAlg_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_QualityCheckAlg

QualityCheckAlg_tag = $(tag)

#cmt_local_tagfile_QualityCheckAlg = $(QualityCheckAlg_tag)_QualityCheckAlg.make
cmt_local_tagfile_QualityCheckAlg = $(bin)$(QualityCheckAlg_tag)_QualityCheckAlg.make

else

tags      = $(tag),$(CMTEXTRATAGS)

QualityCheckAlg_tag = $(tag)

#cmt_local_tagfile_QualityCheckAlg = $(QualityCheckAlg_tag).make
cmt_local_tagfile_QualityCheckAlg = $(bin)$(QualityCheckAlg_tag).make

endif

include $(cmt_local_tagfile_QualityCheckAlg)
#-include $(cmt_local_tagfile_QualityCheckAlg)

ifdef cmt_QualityCheckAlg_has_target_tag

cmt_final_setup_QualityCheckAlg = $(bin)setup_QualityCheckAlg.make
cmt_dependencies_in_QualityCheckAlg = $(bin)dependencies_QualityCheckAlg.in
#cmt_final_setup_QualityCheckAlg = $(bin)QualityCheckAlg_QualityCheckAlgsetup.make
cmt_local_QualityCheckAlg_makefile = $(bin)QualityCheckAlg.make

else

cmt_final_setup_QualityCheckAlg = $(bin)setup.make
cmt_dependencies_in_QualityCheckAlg = $(bin)dependencies.in
#cmt_final_setup_QualityCheckAlg = $(bin)QualityCheckAlgsetup.make
cmt_local_QualityCheckAlg_makefile = $(bin)QualityCheckAlg.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)QualityCheckAlgsetup.make

#QualityCheckAlg :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'QualityCheckAlg'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = QualityCheckAlg/
#QualityCheckAlg::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of libary_header ---------------

QualityCheckAlglibname   = $(bin)$(library_prefix)QualityCheckAlg$(library_suffix)
QualityCheckAlglib       = $(QualityCheckAlglibname).a
QualityCheckAlgstamp     = $(bin)QualityCheckAlg.stamp
QualityCheckAlgshstamp   = $(bin)QualityCheckAlg.shstamp

QualityCheckAlg :: dirs  QualityCheckAlgLIB
	$(echo) "QualityCheckAlg ok"

#-- end of libary_header ----------------

QualityCheckAlgLIB :: $(QualityCheckAlglib) $(QualityCheckAlgshstamp)
	@/bin/echo "------> QualityCheckAlg : library ok"

$(QualityCheckAlglib) :: $(bin)PIDAlg.o $(bin)QualityCheckAlg.o $(bin)Load.o $(bin)Entries.o
	$(lib_echo) library
	$(lib_silent) cd $(bin); \
	  $(ar) $(QualityCheckAlglib) $?
	$(lib_silent) $(ranlib) $(QualityCheckAlglib)
	$(lib_silent) cat /dev/null >$(QualityCheckAlgstamp)

#------------------------------------------------------------------
#  Future improvement? to empty the object files after
#  storing in the library
#
##	  for f in $?; do \
##	    rm $${f}; touch $${f}; \
##	  done
#------------------------------------------------------------------

$(QualityCheckAlglibname).$(shlibsuffix) :: $(QualityCheckAlglib) $(QualityCheckAlgstamps)
	$(lib_silent) cd $(bin); QUIET=$(QUIET); $(make_shlib) "$(tags)" QualityCheckAlg $(QualityCheckAlg_shlibflags)

$(QualityCheckAlgshstamp) :: $(QualityCheckAlglibname).$(shlibsuffix)
	@if test -f $(QualityCheckAlglibname).$(shlibsuffix) ; then cat /dev/null >$(QualityCheckAlgshstamp) ; fi

QualityCheckAlgclean ::
	$(cleanup_echo) objects
	$(cleanup_silent) cd $(bin); /bin/rm -f $(bin)PIDAlg.o $(bin)QualityCheckAlg.o $(bin)Load.o $(bin)Entries.o

#-----------------------------------------------------------------
#
#  New section for automatic installation
#
#-----------------------------------------------------------------

ifeq ($(INSTALLAREA),)
installarea = $(CMTINSTALLAREA)
else
ifeq ($(findstring `,$(INSTALLAREA)),`)
installarea = $(shell $(subst `,, $(INSTALLAREA)))
else
installarea = $(INSTALLAREA)
endif
endif

install_dir = ${installarea}/${CMTCONFIG}/lib
QualityCheckAlginstallname = $(library_prefix)QualityCheckAlg$(library_suffix).$(shlibsuffix)

QualityCheckAlg :: QualityCheckAlginstall

install :: QualityCheckAlginstall

QualityCheckAlginstall :: $(install_dir)/$(QualityCheckAlginstallname)
	@if test ! "${installarea}" = ""; then\
	  echo "installation done"; \
	fi

$(install_dir)/$(QualityCheckAlginstallname) :: $(bin)$(QualityCheckAlginstallname)
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test ! -d "$(install_dir)"; then \
	      mkdir -p $(install_dir); \
	    fi ; \
	    if test -d "$(install_dir)"; then \
	      echo "Installing library $(QualityCheckAlginstallname) into $(install_dir)"; \
	      if test -e $(install_dir)/$(QualityCheckAlginstallname); then \
	        $(cmt_uninstall_area_command) $(install_dir)/$(QualityCheckAlginstallname); \
	        $(cmt_uninstall_area_command) $(install_dir)/$(QualityCheckAlginstallname).cmtref; \
	      fi; \
	      $(cmt_install_area_command) `pwd`/$(QualityCheckAlginstallname) $(install_dir)/$(QualityCheckAlginstallname); \
	      echo `pwd`/$(QualityCheckAlginstallname) >$(install_dir)/$(QualityCheckAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot install library $(QualityCheckAlginstallname), no installation directory specified"; \
	  fi; \
	fi

QualityCheckAlgclean :: QualityCheckAlguninstall

uninstall :: QualityCheckAlguninstall

QualityCheckAlguninstall ::
	@if test ! "${installarea}" = ""; then \
	  cd $(bin); \
	  if test ! "$(install_dir)" = ""; then \
	    if test -d "$(install_dir)"; then \
	      echo "Removing installed library $(QualityCheckAlginstallname) from $(install_dir)"; \
	      $(cmt_uninstall_area_command) $(install_dir)/$(QualityCheckAlginstallname); \
	      $(cmt_uninstall_area_command) $(install_dir)/$(QualityCheckAlginstallname).cmtref; \
	    fi \
          else \
	    echo "Cannot uninstall library $(QualityCheckAlginstallname), no installation directory specified"; \
	  fi; \
	fi




#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),QualityCheckAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)PIDAlg.d

$(bin)$(binobj)PIDAlg.d :

$(bin)$(binobj)PIDAlg.o : $(cmt_final_setup_QualityCheckAlg)

$(bin)$(binobj)PIDAlg.o : $(src)PIDAlg.cxx
	$(cpp_echo) $(src)PIDAlg.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(PIDAlg_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(PIDAlg_cppflags) $(PIDAlg_cxx_cppflags)  $(src)PIDAlg.cxx
endif
endif

else
$(bin)QualityCheckAlg_dependencies.make : $(PIDAlg_cxx_dependencies)

$(bin)QualityCheckAlg_dependencies.make : $(src)PIDAlg.cxx

$(bin)$(binobj)PIDAlg.o : $(PIDAlg_cxx_dependencies)
	$(cpp_echo) $(src)PIDAlg.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(PIDAlg_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(PIDAlg_cppflags) $(PIDAlg_cxx_cppflags)  $(src)PIDAlg.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),QualityCheckAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)QualityCheckAlg.d

$(bin)$(binobj)QualityCheckAlg.d :

$(bin)$(binobj)QualityCheckAlg.o : $(cmt_final_setup_QualityCheckAlg)

$(bin)$(binobj)QualityCheckAlg.o : $(src)QualityCheckAlg.cxx
	$(cpp_echo) $(src)QualityCheckAlg.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(QualityCheckAlg_cppflags) $(QualityCheckAlg_cxx_cppflags)  $(src)QualityCheckAlg.cxx
endif
endif

else
$(bin)QualityCheckAlg_dependencies.make : $(QualityCheckAlg_cxx_dependencies)

$(bin)QualityCheckAlg_dependencies.make : $(src)QualityCheckAlg.cxx

$(bin)$(binobj)QualityCheckAlg.o : $(QualityCheckAlg_cxx_dependencies)
	$(cpp_echo) $(src)QualityCheckAlg.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(QualityCheckAlg_cppflags) $(QualityCheckAlg_cxx_cppflags)  $(src)QualityCheckAlg.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),QualityCheckAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Load.d

$(bin)$(binobj)Load.d :

$(bin)$(binobj)Load.o : $(cmt_final_setup_QualityCheckAlg)

$(bin)$(binobj)Load.o : $(src)components/Load.cxx
	$(cpp_echo) $(src)components/Load.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(Load_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(Load_cppflags) $(Load_cxx_cppflags) -I../src/components $(src)components/Load.cxx
endif
endif

else
$(bin)QualityCheckAlg_dependencies.make : $(Load_cxx_dependencies)

$(bin)QualityCheckAlg_dependencies.make : $(src)components/Load.cxx

$(bin)$(binobj)Load.o : $(Load_cxx_dependencies)
	$(cpp_echo) $(src)components/Load.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(Load_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(Load_cppflags) $(Load_cxx_cppflags) -I../src/components $(src)components/Load.cxx

endif

#-- end of cpp_library ------------------
#-- start of cpp_library -----------------

ifneq (-MMD -MP -MF $*.d -MQ $@,)

ifneq ($(MAKECMDGOALS),QualityCheckAlgclean)
ifneq ($(MAKECMDGOALS),uninstall)
-include $(bin)$(binobj)Entries.d

$(bin)$(binobj)Entries.d :

$(bin)$(binobj)Entries.o : $(cmt_final_setup_QualityCheckAlg)

$(bin)$(binobj)Entries.o : $(src)components/Entries.cxx
	$(cpp_echo) $(src)components/Entries.cxx
	$(cpp_silent) $(cppcomp) -MMD -MP -MF $*.d -MQ $@ -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(Entries_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(Entries_cppflags) $(Entries_cxx_cppflags) -I../src/components $(src)components/Entries.cxx
endif
endif

else
$(bin)QualityCheckAlg_dependencies.make : $(Entries_cxx_dependencies)

$(bin)QualityCheckAlg_dependencies.make : $(src)components/Entries.cxx

$(bin)$(binobj)Entries.o : $(Entries_cxx_dependencies)
	$(cpp_echo) $(src)components/Entries.cxx
	$(cpp_silent) $(cppcomp) -o $@ $(use_pp_cppflags) $(QualityCheckAlg_pp_cppflags) $(lib_QualityCheckAlg_pp_cppflags) $(Entries_pp_cppflags) $(use_cppflags) $(QualityCheckAlg_cppflags) $(lib_QualityCheckAlg_cppflags) $(Entries_cppflags) $(Entries_cxx_cppflags) -I../src/components $(src)components/Entries.cxx

endif

#-- end of cpp_library ------------------
#-- start of cleanup_header --------------

clean :: QualityCheckAlgclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(QualityCheckAlg.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

QualityCheckAlgclean ::
#-- end of cleanup_header ---------------
#-- start of cleanup_library -------------
	$(cleanup_echo) library QualityCheckAlg
	-$(cleanup_silent) cd $(bin); /bin/rm -f $(library_prefix)QualityCheckAlg$(library_suffix).a $(library_prefix)QualityCheckAlg$(library_suffix).s? QualityCheckAlg.stamp QualityCheckAlg.shstamp
#-- end of cleanup_library ---------------
