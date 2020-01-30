:orphan:

Refactoring
===========

  1. change or action
  2. phenomenon / effect
  3. solution
  4. example

There are some changes which don't change fingerprints at all, and unlikely to cause regression.
These changes include renaming functions and variables, and method extraction.

For example, we extract some part of ``handleUpperCommand()`` function in the Udp module to a new function:

.. literalinclude:: ../Udp_extract.cc
   :diff: ../Udp_orig.cc

.. **Why doesn't it change the fingerprint?**

The refactoring doesn't change the fingerprint because the code is functionally the same; doesn't cause any new events or data packets, doesn't change timing, or anything that the fingerprint takes into account.

TODO: PASS
