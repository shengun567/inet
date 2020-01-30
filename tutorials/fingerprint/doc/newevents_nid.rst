.. :orphan:

New events - NID
================

Another way of dealing with new events is to use the network communication fingerprint calculator.

When a change introduces new events to the simulation and breaks fingerprints, an option is to use a different / alternative fingerprint calculator, not the default one. INET features the Network Communication Fingerprint Calculator, which extends the default one (as that normal fingerprints can be used alongside it). This fingerprint calculator uses the communication between modules, such as messages, etc, TODO, as ingredients. TODO

This only takes into account/uses the communication between nodes.
Thus protocol implementation details don't matter...only the data content of the packets.
The fingerprint calculator has three available ingredients:

- ``N``: Network node path
- ``I``: Network interface path
- ``D``: Network data

To use it, add the following line to the ``General`` configuration:

.. literalinclude:: ../omnetpp.ini
   :start-at: General
   :end-at: class
   :language: ini

TODO the default and the NID can be mixed
