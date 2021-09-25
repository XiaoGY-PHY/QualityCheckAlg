# echo "cleanup QualityCheckAlg QualityCheckAlg-00-00-01 in /workfs2/bes/xiaogy/Boss706a/Analysis"

if test "${CMTROOT}" = ""; then
  CMTROOT=/cvmfs/bes3.ihep.ac.cn/bes3sw/ExternalLib/SLC6/contrib/CMT/v1r25; export CMTROOT
fi
. ${CMTROOT}/mgr/setup.sh
cmtQualityCheckAlgtempfile=`${CMTROOT}/mgr/cmt -quiet build temporary_name`
if test ! $? = 0 ; then cmtQualityCheckAlgtempfile=/tmp/cmt.$$; fi
${CMTROOT}/mgr/cmt cleanup -sh -pack=QualityCheckAlg -version=QualityCheckAlg-00-00-01 -path=/workfs2/bes/xiaogy/Boss706a/Analysis  $* >${cmtQualityCheckAlgtempfile}
if test $? != 0 ; then
  echo >&2 "${CMTROOT}/mgr/cmt cleanup -sh -pack=QualityCheckAlg -version=QualityCheckAlg-00-00-01 -path=/workfs2/bes/xiaogy/Boss706a/Analysis  $* >${cmtQualityCheckAlgtempfile}"
  cmtcleanupstatus=2
  /bin/rm -f ${cmtQualityCheckAlgtempfile}
  unset cmtQualityCheckAlgtempfile
  return $cmtcleanupstatus
fi
cmtcleanupstatus=0
. ${cmtQualityCheckAlgtempfile}
if test $? != 0 ; then
  cmtcleanupstatus=2
fi
/bin/rm -f ${cmtQualityCheckAlgtempfile}
unset cmtQualityCheckAlgtempfile
return $cmtcleanupstatus

