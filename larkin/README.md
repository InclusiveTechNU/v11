# Larkin

Larkin is a cross-platform C++ library that exposes automation and
accessibility APIs at a low-level. V11 is powered with by Larkin through an RPC
service that retrieves requests from V11's sandboxed environment.

*Client*: Provides the C++ JS runtime bindings for Larkin.

*Service*: The RPC Daemon Service that runs whenever a JS runtime creates a V11
client process.

*Core*: Core provides the Larkin cross-platform C++ apis.

*Protos*: Protos defines the protobufs that are used to communicate between
the Larkin RPC client and service.
