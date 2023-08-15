Logging Service
=================
The Logging service is intended to be a mechanism that provides a means to print in the context
of a secure partition.  All other secure partitions in a given environment will utilize a
handler to push any data to this SP. The current default behavior is where the logging service
will send the data to a UART peripheral viewable by a terminal device (see: :ref:`UART backend`).

In case the logging with the logging SP fails (e.g. in case the logging SP is not deployed, still
booting, etc.) log messages fall back to the default logging mechanism.

UART backend
------------
The UART backend for the logging SP outputs the log messages to an UART device. It relies on an
UART platform adapter that provides a generic interface to interact with an UART device.
The exact driver implementation is to be provided by the platform.
The platform specific driver configuration (base-address) is hosted in the SP manifest.
Platform code is responsible for reading the config data from the config store upon boot.
Currently a PL011 driver is provided for the *AEM FVP* platform.

Testing the Logging Service
-------------------------------
Component-Level Test Suites
'''''''''''''''''''''''''''
The logging components will be targeted by component-test and unit-test cases.

Service-Level Test Suites
'''''''''''''''''''''''''
*ts-service-test* may implement logging service calls, although verifying the log messages would
be difficult, so the scope is limited. (Unit and component test cases can account for this.)

Environment Tests
'''''''''''''''''
The logging SP's UART backend relies on the UART peripheral. Test have been added to the
*env_test* SP deployment to check the basic functionality of the UART device, but the
verification of the results is not possible, as the peripheral does not provide a way
(e.g. error bit) to check whether the printing (*putc*) was successful.
Tests included in the *env_test* SP deployment may be invoked from Linux user-space using the
*ts-remote-test/arm-linux* deployment.


*Copyright (c) 2023, Arm Limited and Contributors. All rights reserved.*

SPDX-License-Identifier: BSD-3-Clause
