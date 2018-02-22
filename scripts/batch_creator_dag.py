channel="mujets"
path="/eos/atlas/atlascerngroupdisk/phys-top/toproperties/ttgamma/v010/CR1S/"+channel+"/"
nn_file="model4_150_singlelepton_ELD.json"
ppt_file="weights_PPT-2018-02-08-1.root"
egammaSF="EFakeSFs_Final.root"
hfakeSF="hfake_SF_final_3D.root"
kfactor_files="kfactor_sinlepton_theory_fineBin.root,kfactor_dilepton_theory_fineBin.root"


def printHeader(f,jobname):
  f.write("executable            = /afs/cern.ch/work/j/jwsmith/github/ttgamma_lwtnn_injection/build_batch/"+channel+"/nnInjector\n")
  f.write("transfer_input_files  = "+nn_file+","+ppt_file+","+egammaSF+","+hfakeSF+","+kfactor_files+"\n")
  f.write("getenv                = True\n")
  f.write("JobBatchName	      = "+jobname+"\n")
  f.write('+JobFlavour           = "testmatch"\n')
  f.write("\n")


from os import listdir
from os.path import isfile, join
from random import shuffle

ntuples = [f for f in listdir(path) if isfile(join(path, f))]
shuffle(ntuples)

ntuples = [i for i in ntuples if 'p2952' not in i]
ntuples = [i for i in ntuples if 'p2950' not in i]
ntuples = [i for i in ntuples if '98pc' not in i]


def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i + n]

chunked_list = list(chunks(ntuples,10))
files=[]

for chunk in range(0,len(chunked_list)):
    filename=channel+"_"+str(chunk)+".sub"
    files.append(filename)
    f = open(filename, 'w')
    printHeader(f,filename.strip(".sub"))
    for i in chunked_list[chunk]:
      f.write("output = output/$(ClusterId).$(ProcId)."+i.rstrip(".root")+".out \n")
      f.write("error = error/$(ClusterId).$(ProcId)."+i.rstrip(".root")+".err \n")
      f.write("log = log/$(ClusterId).$(ProcId)."+i.rstrip(".root")+".log \n")
      f.write("arguments = "+i+"\n")
      f.write("queue\n")
      f.write("\n")
    f.close()

f2 = open(channel+"_DAG.dag", 'w')
for j in files:
  f2.write("JOB "+j.strip(".sub")+" "+j+"\n")

f2.write("\n")
for k in range(0,len(files)):
  if k==len(files)-1:continue
  parent=files[k].strip(".sub")
  child=files[k+1].strip(".sub")
  f2.write("PARENT "+parent+" CHILD "+child+"\n")
f2.close()
