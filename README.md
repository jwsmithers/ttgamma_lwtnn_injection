## ttgamma_lwtnn_injection

This code reprocesses ntuples for the ttgamma analysis. Examples of operations performed:

* Add new variables
* Include new systematic variables

If given an ntuple with multiple trees (i.e. systematics), it will loop on all trees automatically and perform the same operation.

The only file you should ever have to tweak is `Root/nnInjector.cxx` or `include/nnInjector.h`.

_Unfortunately, it's not completely channel aware, which means there are a few hardcoded things you need to adjust when switching channels. You also need to keep in mind which ELD you are using. Copying and pasting it into the build directory minimizes chances of screwing up. I normally build ejets, mujets and dilepton seperatly. (Since dilepton is quick.)_

See [Setting the Configuration Before Each Run](#remember) to know exactly what to tweak between each run.

## Local Usage
```
source setup
mkdir -p build/ejets ; cd build/ejets # Can also be mujets or dilepton 
cmake ../../
make
cp ../../json/model4_150_singlelepton_ELD.json . # NB, if dilepton, cp ../../json/model4_300_dilepton_ELD.json .
cp ../../systematics/weight_PPT.root . # If dilepton, copying won't hurt, but this file won't be used
./nnInjector some_root_ntuple.root
```

The way that this is called means you can parallellize this to your hearts content on multiple nodes in say a bash script such as 
```
./nnInjector 301XXX.enugamma.p2952.v007.001.root
./nnInjector 301XXX.munugamma.p2952.v007.001.root
./nnInjector 301XXX.taunugamma.p2952.v007.001.root
./nnInjector 3641XX.Wenu.p2952.v007.001.root
./nnInjector 3641XX.Wmunu.p2952.v007.001.root
./nnInjector 3641XX.Wtaunu.p2952.v007.001.root
```
Alternatively, you can use the batch system which makes this very fast...

## Batch system usage
```
source setup
mkdir -p build_batch/ejets; cd build_batch/ejets
cmake ../../
make
cp ../../json/model4_150_singlelepton_ELD.json .
cp ../../systematics/weight_PPT.root .
cp ../../scripts/batch_creator.py . # Set first 3 variables in script. First is the samples from which directory we want to read. Set the correct NN file.
python batch_creator.py > ejets_batch.sh  # Have a look at output to see if path to executable is correct.
mkdir error log output
condor_submit ejets_batch.sh
```
## <a name="remember"></a> Setting the Configureation Before Each Run

There are 3 things to worry about before each run in `Root/nnInjector.cxx`:
1) Where are you reading the files from? The variable to set it `path` (around line 259).
2) Which neural network file are you using? (Single or dilepton channel). Variable to set is `in_file_name` (around line 250)
3) Which channels are you runnnig over? (ejets or mujets or ee, emu, ee). You can run over all at once or one by one. But it doesn't make sense to do single lepton and dilepton together since the NN files are different. Variable is `channels` (around line 262)
4) Where are you saving to? Variable is `myPath` (around line 266).

This could obviously be cleaned up a little, feel free to submit pull requests :).

