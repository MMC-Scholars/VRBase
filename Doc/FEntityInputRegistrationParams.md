# `FEntityInputRegistrationParams` Struct

`FEntityInputRegistrationParams` is used to record the pressed and released states of motion controllers using [`FEntityRegistrationButtons`](./FEntityInputRegistrationButtons.md). This should not be instantiated otherwise.

| Order | | Member | Description |
| --- | --- | --- | --- |
| 1 | [`FEntityInputRegistrationButtons`](./FEntityInputRegistrationButtons.md) | m_onPressed | `Bool` struct containing buttons pressed. Accessible via UProperty |
| 2 | [`FEntityInputRegistrationButtons`](./FEntityInputRegistrationButtons.md) | m_onReleased | `Bool` struct containing buttons released. Accessible via UProperty |
