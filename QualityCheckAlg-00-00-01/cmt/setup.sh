# echo "setup QualityCheckAlg QualityCheckAlg-00-00-01 in /workfs2/bes/xiaogy/Boss706a/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtQualityCheckAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtQualityCheckAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt setup -sh -pack=QualityCheckAlg -version=QualityCheckAlg-00-00-01 -path=/workfs2/bes/xiaogy/Boss706a/Analysis  -no_cleanup $* >${cmtQualityCheckAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt setup -sh -pack=QualityCheckAlg -version=QualityCheckAlg-00-00-01 -path=/workfs2/bes/xiaogy/Boss706a/Analysis  -no_cleanup $* >${cmtQualityCheckAlgtempfile}"
  cmtsetupstatus=2
  /bin/rm -f ${cmtQualityCheckAlgtempfile}
  unset cmtQualityCheckAlgtempfile
  return $cmtsetupstatus
fi
cmtsetupstatus=0
. ${cmtQualityCheckAlgtempfile}
if test $? != 0 ; then
  cmtsetupstatus=2
fi
/bin/rm -f ${cmtQualityCheckAlgtempfile}
unset cmtQualityCheckAlgtempfile
return $cmtsetupstatus

