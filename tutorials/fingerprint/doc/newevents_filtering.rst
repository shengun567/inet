:orphan:

New events - filtering
======================

  1. change or action
  2. phenomenon / effect
  3. solution
  4. example

Some changes in the model can add new events to the simulation. These events inevitably change the fingerprints but not necessarily invalidate the model. One option is to filter out the modules in which the new events take place. Taking into account the rest migth show that the simulation trajectory in fact stayed that same.

To filter out the modules, run the fingerprint test with the ``--fingerprint-modules`` command line option, e.g.:

.. TODO example

.. code-block:: bash

   $ inet_fingerprinttest -a --fingerprint-modules='"not fullPath=~**.wlan[*].mac.**"'

Then, update the fingerprints, make the change, and run the fingerprints again.

TODO example
