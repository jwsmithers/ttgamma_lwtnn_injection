export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

setupATLAS -q

lsetup "cmake 3.7.0"

lsetup "root 6.12.04-x86_64-slc6-gcc62-opt"

localSetupSFT -q releases/LCG_88/eigen/3.2.9 --cmtconfig x86_64-slc6-gcc62-opt
localSetupBoost -q boost-1.60.0-python2.7-x86_64-slc6-gcc62
EIGEN_INC=$SFT_HOME_eigen/include/eigen3
BOOST_INC=$ALRB_BOOST_ROOT/include
export CPLUS_INCLUDE_PATH=$EIGEN_INC:$BOOST_INC


