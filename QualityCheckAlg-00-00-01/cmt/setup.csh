# echo "setup QualityCheckAlg QualityCheckAlg-00-00-01 in /workfs2/bes/xiaogy/Boss706a/Analysis"

if ( $?CMTROOT == 0 ) then
  setenv CMTROOT /cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25
endif
source ${CMTROOT}/mgr/setup.csh
set cmtQualityCheckAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if $status != 0 then
  set cmtQualityCheckAlgtempfile=/tmp/cmt.$$
endif
${CMTROOT}/mgr/cmt setup -csh -pack=QualityCheckAlg -version=QualityCheckAlg-00-00-01 -path=/workfs2/bes/xiaogy/Boss706a/Analysis  -no_cleanup $* >${cmtQualityCheckAlgtempfile}
if ( $status != 0 ) then
  echo "${CMTROOT}/mgr/cmt setup -csh -pack=QualityCheckAlg -version=QualityCheckAlg-00-00-01 -path=/workfs2/bes/xiaogy/Boss706a/Analysis  -no_cleanup $* >${cmtQualityCheckAlgtempfile}"
  set cmtsetupstatus=2
  /bin/rm -f ${cmtQualityCheckAlgtempfile}
  unset cmtQualityCheckAlgtempfile
  exit $cmtsetupstatus
endif
set cmtsetupstatus=0
source ${cmtQualityCheckAlgtempfile}
if ( $status != 0 ) then
  set cmtsetupstatus=2
endif
/bin/rm -f ${cmtQualityCheckAlgtempfile}
unset cmtQualityCheckAlgtempfile
exit $cmtsetupstatus

