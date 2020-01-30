:orphan:

Renaming
========

- rename modules in the model
- the fingerprint breaks because by default its tplx (or is it ?)
- so drop the p (full path) from the ingredients
- rerun fingerprints without p
- make the change
- the fingerprints match



sturcture

- X change breaks fingerprint
- because something
- solution
- example

1. change or action
2. phenomenon / effect
3. solution
4. example

Renaming modules can cause the fingerprints to change, because the default ingredients (``tplx``) contain the full path, thus the module name as well. Renaming modules can cause regression in some cases, e.g. when some functionality in the model depends on module names.

TODO false positive

TODO example for false positive

To filter out false positives, the fingerprints need to be calculated without the full path:

- Before making the change, rerun fingerprints without the full path ingredient
- Update fingerprints, as the new values can be accepted since no change taken place
- Perform renaming
- Run fingerprints again

Now, if fingerprints don't pass, it indicates that the change really broke something in the model/introduced a regression.

For example, TODO:

TODO example for no regression (rename some module)

.. literalinclude:: ../LinkLayerNodeBase.ned.modified
   :diff: ../LinkLayerNodeBase.ned.orig

.. literalinclude:: ../NetworkLayerNodeBase.ned.modified
   :diff: ../NetworkLayerNodeBase.ned.orig

TODO example for regression (rename some module that is referred to by name, such as ip or routing table)

Results
