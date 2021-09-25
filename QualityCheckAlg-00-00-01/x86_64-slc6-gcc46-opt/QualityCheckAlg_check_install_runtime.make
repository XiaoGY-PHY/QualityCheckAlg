#-- start of make_header -----------------

#====================================
#  Document QualityCheckAlg_check_install_runtime
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

cmt_QualityCheckAlg_check_install_runtime_has_no_target_tag = 1

#--------------------------------------------------------

ifdef cmt_QualityCheckAlg_check_install_runtime_has_target_tag

tags      = $(tag),$(CMTEXTRATAGS),target_QualityCheckAlg_check_install_runtime

QualityCheckAlg_tag = $(tag)

#cmt_local_tagfile_QualityCheckAlg_check_install_runtime = $(QualityCheckAlg_tag)_QualityCheckAlg_check_install_runtime.make
cmt_local_tagfile_QualityCheckAlg_check_install_runtime = $(bin)$(QualityCheckAlg_tag)_QualityCheckAlg_check_install_runtime.make

else

tags      = $(tag),$(CMTEXTRATAGS)

QualityCheckAlg_tag = $(tag)

#cmt_local_tagfile_QualityCheckAlg_check_install_runtime = $(QualityCheckAlg_tag).make
cmt_local_tagfile_QualityCheckAlg_check_install_runtime = $(bin)$(QualityCheckAlg_tag).make

endif

include $(cmt_local_tagfile_QualityCheckAlg_check_install_runtime)
#-include $(cmt_local_tagfile_QualityCheckAlg_check_install_runtime)

ifdef cmt_QualityCheckAlg_check_install_runtime_has_target_tag

cmt_final_setup_QualityCheckAlg_check_install_runtime = $(bin)setup_QualityCheckAlg_check_install_runtime.make
cmt_dependencies_in_QualityCheckAlg_check_install_runtime = $(bin)dependencies_QualityCheckAlg_check_install_runtime.in
#cmt_final_setup_QualityCheckAlg_check_install_runtime = $(bin)QualityCheckAlg_QualityCheckAlg_check_install_runtimesetup.make
cmt_local_QualityCheckAlg_check_install_runtime_makefile = $(bin)QualityCheckAlg_check_install_runtime.make

else

cmt_final_setup_QualityCheckAlg_check_install_runtime = $(bin)setup.make
cmt_dependencies_in_QualityCheckAlg_check_install_runtime = $(bin)dependencies.in
#cmt_final_setup_QualityCheckAlg_check_install_runtime = $(bin)QualityCheckAlgsetup.make
cmt_local_QualityCheckAlg_check_install_runtime_makefile = $(bin)QualityCheckAlg_check_install_runtime.make

endif

#cmt_final_setup = $(bin)setup.make
#cmt_final_setup = $(bin)QualityCheckAlgsetup.make

#QualityCheckAlg_check_install_runtime :: ;

dirs ::
	@if test ! -r requirements ; then echo "No requirements file" ; fi; \
	  if test ! -d $(bin) ; then $(mkdir) -p $(bin) ; fi

javadirs ::
	@if test ! -d $(javabin) ; then $(mkdir) -p $(javabin) ; fi

srcdirs ::
	@if test ! -d $(src) ; then $(mkdir) -p $(src) ; fi

help ::
	$(echo) 'QualityCheckAlg_check_install_runtime'

binobj = 
ifdef STRUCTURED_OUTPUT
binobj = QualityCheckAlg_check_install_runtime/
#QualityCheckAlg_check_install_runtime::
#	@if test ! -d $(bin)$(binobj) ; then $(mkdir) -p $(bin)$(binobj) ; fi
#	$(echo) "STRUCTURED_OUTPUT="$(bin)$(binobj)
endif

${CMTROOT}/src/Makefile.core : ;
ifdef use_requirements
$(use_requirements) : ;
endif

#-- end of make_header ------------------
#-- start of cmt_action_runner_header ---------------

ifdef ONCE
QualityCheckAlg_check_install_runtime_once = 1
endif

ifdef QualityCheckAlg_check_install_runtime_once

QualityCheckAlg_check_install_runtimeactionstamp = $(bin)QualityCheckAlg_check_install_runtime.actionstamp
#QualityCheckAlg_check_install_runtimeactionstamp = QualityCheckAlg_check_install_runtime.actionstamp

QualityCheckAlg_check_install_runtime :: $(QualityCheckAlg_check_install_runtimeactionstamp)
	$(echo) "QualityCheckAlg_check_install_runtime ok"
#	@echo QualityCheckAlg_check_install_runtime ok

#$(QualityCheckAlg_check_install_runtimeactionstamp) :: $(QualityCheckAlg_check_install_runtime_dependencies)
$(QualityCheckAlg_check_install_runtimeactionstamp) ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.6.a/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs2/bes/xiaogy/Boss706a/InstallArea/share
	$(silent) cat /dev/null > $(QualityCheckAlg_check_install_runtimeactionstamp)
#	@echo ok > $(QualityCheckAlg_check_install_runtimeactionstamp)

QualityCheckAlg_check_install_runtimeclean ::
	$(cleanup_silent) /bin/rm -f $(QualityCheckAlg_check_install_runtimeactionstamp)

else

#QualityCheckAlg_check_install_runtime :: $(QualityCheckAlg_check_install_runtime_dependencies)
QualityCheckAlg_check_install_runtime ::
	$(silent) /cvmfs/bes3.ihep.ac.cn/bes3sw/Boss/7.0.6.a/BesPolicy/BesPolicy-01-05-05/cmt/bes_check_installations.sh -files= -s=../share *.txt   -installdir=/workfs2/bes/xiaogy/Boss706a/InstallArea/share

endif

install ::
uninstall ::

#-- end of cmt_action_runner_header -----------------
#-- start of cleanup_header --------------

clean :: QualityCheckAlg_check_install_runtimeclean ;
#	@cd .

ifndef PEDANTIC
.DEFAULT::
	$(echo) "(QualityCheckAlg_check_install_runtime.make) $@: No rule for such target" >&2
else
.DEFAULT::
	$(error PEDANTIC: $@: No rule for such target)
endif

QualityCheckAlg_check_install_runtimeclean ::
#-- end of cleanup_header ---------------
