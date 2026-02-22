Software Component template
###########################

Introduction
************

Describe the purpose of the component. Why does it exist? What are the major functions?


References
**********

Other relevant documents, e.g. ISO standards, whitepapers, etc.


Static architecture
*******************

Component
=========

..  swc:: comp1
    :provides: The interface provided by the component. This is the interface that other components can use to interact with this component.
    :requires: The interface required by the component. This is the interface that this component needs to interact with other components.

Public interfaces
=================

..  sw-if:: comp1Unit1.h

    Public interface of comp1Unit1.

    ..  sw-ifelement:: Comp1Unit1PublicFunction()
        :arguments:     return: [0,100];         input: [0,10];

        Description of the function.

        **Arguments:**

        - **input**: Describe the meaning of each argument.

        **Return values:** Describe the meaning of the return value.
          
        **Restrictions:** Restrictions of the funciton if nany



Requirements
************

.. toctree::
    :maxdepth: 1

    ./1_swcReq/comp1Req.rst


Design documentation
********************

.. toctree::
    :maxdepth: 1

    ./2_design/comp1Comp1.rst


Code documentation
******************


.. toctree::
    :maxdepth: 1

    ./2_design/comp1Cfg.rst
    ./2_design/comp1Unit1.rst

Unit tests
******************

.. toctree::
    :maxdepth: 1

    ./6_test/comp1.rst
