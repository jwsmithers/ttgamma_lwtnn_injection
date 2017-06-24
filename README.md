#Usage

`source setup`

`mkdir build ; cd build`

`cmake ../`

`make`

`./nnInjector some_root_ntuple.root`

The way that this is called means you can parallellize this to your hearts content.

## Example

`source setup`

`mkdir build_Wrelated ; cd build_Wrelated`

`cmake ../`

`make`

`sh Wrelated.sh`

Where Wrelated.sh looks like this:

```
./nnInjector 301XXX.enugamma.p2952.v007.001.root
./nnInjector 301XXX.munugamma.p2952.v007.001.root
./nnInjector 301XXX.taunugamma.p2952.v007.001.root
./nnInjector 3641XX.Wenu.p2952.v007.001.root
./nnInjector 3641XX.Wmunu.p2952.v007.001.root
./nnInjector 3641XX.Wtaunu.p2952.v007.001.root
```

## Remember...

*  to set your to and from path in `Root/nnInjector.cxx`
*  to cutomize your `m_add_branches` function. Each nn is different and so will need tweaking.
*  to brush you teeth
