export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
alias setupATLAS='source ${ATLAS_LOCAL_ROOT_BASE}/user/atlasLocalSetup.sh'

setupATLAS -q
# localSetupGcc gcc492_x86_64_slc6
#localSetupROOT -q

lsetup "cmake 3.6.0"
#lsetup "lcgenv -p LCG_88Py3 x86_64-slc6-gcc49-opt Python"
#lsetup "lcgenv -p LCG_88Py3 x86_64-slc6-gcc49-opt pip"
#lsetup "lcgenv -p LCG_88Py3 x86_64-slc6-gcc49-opt h5py"
#lsetup "lcgenv -p LCG_88Py3 x86_64-slc6-gcc49-opt Boost"
#lsetup "lcgenv -p LCG_88Py3 x86_64-slc6-gcc49-opt eigen"
#lsetup "lcgenv -p LCG_88Py3 x86_64-slc6-gcc49-opt gdb"

lsetup "lcgenv -p LCG_88 x86_64-slc6-gcc49-opt ROOT"
lsetup "lcgenv -p LCG_88 x86_64-slc6-gcc49-opt Python"
lsetup "lcgenv -p LCG_88 x86_64-slc6-gcc49-opt pip"
lsetup "lcgenv -p LCG_88 x86_64-slc6-gcc49-opt h5py"
lsetup "lcgenv -p LCG_88 x86_64-slc6-gcc49-opt gdb"

localSetupSFT -q releases/LCG_88/eigen/3.2.9
localSetupBoost -q boost-1.60.0-python2.7-x86_64-slc6-gcc49
EIGEN_INC=$SFT_HOME_eigen/include/eigen3
BOOST_INC=$ALRB_BOOST_ROOT/include
export CPLUS_INCLUDE_PATH=$EIGEN_INC:$BOOST_INC
