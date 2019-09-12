# Type Definitions

VRBase uses unique definitions to describe commonly used types present throughout the library.

## Typedefs

| | Type | Description |
| --- | --- | --- |
| `unsigned char` | byte | A single bit |
| `unsigned short` | eindex | Entity index |
| `float` | ftime | Time in seconds |
| `unsigned int` | uint | Unsigned int |
| `unsigned long long` | ulong | Unsigned long |
| `unsigned short` | ushort | Unsigned short |
| `float` | vec | Vector world space units |

## Structs

- FEntityInputRegistrationButtons
  | | Member | Description |
  | --- | --- | --- |
  | `bool` | m_AX | Returns true if the AX buttons are active. Accessible via UProperty |
  | `bool` | m_BY | Returns true if the BY buttons are active. Accessible via UProperty |
  | `bool` | m_TRIGGER | Returns true if the TRIGGER buttons are active. Accessible via UProperty |
  | `bool` | m_GRIP | Returns true if the GRIP buttons are active. Accessible via UProperty |
  | `bool` | m_MENU | Returns true if the MENU buttons are active. Accessible via UProperty |
  | `bool` | m_STICK | Returns true if the STICK buttons are active. Accessible via UProperty |
- FEntityInputRegistrationParams  
  | | Member | Description |
  | --- | --- | --- |
  | FEntityInputRegistrationButtons | m_onPressed | `Bool` struct containing buttons pressed. Accessible via UProperty |
  | FEntityInputRegistrationButtons | m_onReleased | `Bool` struct containing buttons released. Accessible via UProperty |
- FPawnInstruction
  | | Member | Description |
  | --- | --- | --- |
  | `bool` | changeOnButtonPress | If true, will switch instruction on button press. Otherwise, will switch based on time. Accessible via UProperty |
  | `FColor` | color | The instruction color. Default is white. Accessible via UProperty |
  | `EControllerHand` | hand | The hand the instruction should be displayed near. Default is `Right`. Accessible via UProperty |
  | `FText` | text | The instruction text to display. Accessible via UProperty |
  | `ftime` | timedChange | The time needed to switch instructions. Default is 5. Accessible via UProperty |
