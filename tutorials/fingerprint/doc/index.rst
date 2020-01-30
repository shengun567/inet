.. :orphan:

Fingerprint
===========

Goals
-----

  The introduction

  - what are fingerprints and what they're good for
    #development #regressiontesting #verification

  - what are the various ingredients? and where to find them
  - what other kinds of fingerprint calculators are available, besides the default one ?

  - how to run it? the different possibilities (ini/fingerprint tool)

  - what is this tutorial about ?
  - how is this tutorial structured ?

  The steps

----------------------------------------------------------

  so

  -fingerprint testing is useful and lowcost for regression testing during model development
  -omnetpp has the fingerprint mechanism builtin and inet has the fingerprint test tool
  for convenience
  -a fingerprint is a hash value, which is calculated during a simulation run from certain properties
  of a simulation, such as time of events, module names, packet data, etc.
  -it is constantly updated
  -it is a characteristic of the simulation's trajectory
  -it is good for regression testing because a change in the fingerprint means the trajectory changed
  -useful during development to see if some change breaks the model's correct behavior

**- what are fingerprints and what they're good for
#development #regressiontesting #verification**

**Introduction**
Fingerprint testing is a useful and low-cost tool for regression testing during model development.
A fingerprint is a hash value, which is calculated during a simulation run and is characteristic of the simulation's trajectory. After the change in the model, a change in the fingerprint can indicate that the model no longer works correctly.
When the fingerprints stay the same after a change in the model, the model can be assumed to be still working correctly. thus protecting against regressions

What the tutorial is about?
---------------------------

Its about the workflow of regression testing. The typical actions done during development and how they might affect fingerprints and how to verify the correctness of the model.
The different cases.

About fingerprints in more detail
---------------------------------

Fingerprint testing is a useful and low-cost tool for regression testing during model development.
A fingerprint is a hash value, which is calculated during a simulation run from certain properties of the simulation, such as time of events, module names, packet data, etc.

Fingerprint testing is a useful and low-cost tool for regression testing during model development.
A fingerprint is a hash value, which is calculated during a simulation run from certain "ingredients", i.e. properties of the simulation such as time of events, module names, packet data, etc.

The hash is continually updated until the end of the simulation (or some defined time limit),
resulting in a fingerprint value.

**V1** This value is characteristic of the simulation's trajectory; a fingerprint change indicates a change in the trajectory.

**V2** This value is characteristic of the simulation's trajectory. It is useful for regression testing because a change in the fingerprint after a change in the model means the trajectory changed.
It is useful during development to see if some change in the model breaks the model's correct behavior.

TODO: the workflow is calculate the fingerprint when the model is assumed to work correctly,
before introducing a change. After the change, run the fingerprint test again, and see if the
fingerprints match. if not, the change likely broke something in the model.
One needs to examine if the change in fact did break something, or was expected.
Running a fingerprint with other ingredients might help verify that the model is correct.

**- what are the various ingredients? and where to find them**

  TODO: maybe this shouldnt be here but in one of the steps

  The fingerprint ingredients are actually can be specified...

  the fingerprint is a 32 bit value, and also it contains the ingredients, which are denoted by a letter

  such as abcd-ef01-1248-abcd/tplx -> more like 32 bits

  the list of ingredients are in the manual

The fingerprint is a 32-bit hexadecimal value, upended by the ingredients used for calculating it, denoted by letters:

TODO: example fingerprint

.. code-block:: text

   53de-64a7/tplx

In this example, ``t`` means time of event, ``p`` the full path of modules, ``l`` the message length, and ``x`` the extra data added programatically. Other possible ingredients include various properties of messages, modules and results. For the complete list, check out the TODO.

The fingerprints can be specified in the ini file for each configuration. if a fingerprint is specified, it will be calculated. so if you wanna calculate the fingerprint for a config X,
you just say:

| [Config X]
| network = Y
| fingerprint = 0000-0000/tplx

you just specify a value and the ingredients and it will be calculated and the 0000-0000 can be replaced by the resulting value.

TODO: qtenv prints the fingerprint

also, the fingerprint is calculated whether the simulation is run with qtenv or from the command line.

However, there is a more convenient way in INET, the fingerprint tool.

It automates the process to help with development.

The fingerprint tool
--------------------

- the fingerprint tool can automate the process
- its a command line tool, found in inet/tests/fingerprint -> actually, its inet/bin
- its the inet_fingerprinttest script

- csv file format
- reports PASS, FAIL or ERROR
- creates files
- can be updated by overwriting
- can be run in release or debug
- can be filtered with -m which is a regex?
- for more info -h

The fingerprint tool is useful for automating fingerprint tests/is a conventient way to run fingerprint tests. It is located in the inet/bin folder, and when the inet directory is added to the PATH, it can be run from any directory (inet subdirectory?).
By default, the script runs all simulations defined in .csv files in the current folder.
The set of simulations can be filtered with the ``-m`` command line option.

Note that ``-h`` lists all available options.

A line in the .csv file defines a simulation run, by specifying the working directory, command line arguments, sim time limit, fingerprint+ingredients, expected result, and tags.
The result can either be PASS, FAIL or ERROR.

It also creates additional .csv files:

- an UPDATED file, which has the fingerprints just calculated for all lines
- a FAILED file, which contains just the lines for the failed simulations, with the calculated fingerprint. This file is useful for re-running just the simulations with failed fingerprints

The updated file can be used to overwrite the original one to accept the new fingerprints.

The steps
---------

.. toctree::
   :maxdepth: 1

   first
   refactoring
   renaming
   newevents_filtering
   newevents_nid

.. .. toctree::
      :maxdepth: 1
      :glob:

      *
