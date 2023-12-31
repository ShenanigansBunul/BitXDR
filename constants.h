//
// Created by sergi on 12/18/2023.
//

#ifndef BITXDR_CONSTANTS_H
#define BITXDR_CONSTANTS_H

namespace constants {
    constexpr long long incidentDeltaTime = 1000 * 60 * 60 * 2; //maximum time from the alert that created the incident (2h)

    constexpr bool print_measured_time = true;

    constexpr const char message_instructions[] = "Usage: BitXDR.exe input.json output.json";
    constexpr const char message_input_file_nonexistent[] = "Error: Input file not found.";
    constexpr const char message_input_file_not_open[] = "Error: Cannot open input file.";
    constexpr const char message_output_file_not_open[] = "Error: Cannot open output file.";
    constexpr const char message_input_parse_error[] = "Error: Parse error in input JSON file:";
    constexpr const char message_input_pc_warning[] = "Warning: Incorrect format in input JSON file in pcs:";
    constexpr const char message_input_user_warning[] = "Warning: Incorrect format in input JSON file in users:";
    constexpr const char message_input_alert_warning[] = "Warning: Incorrect format in input JSON file in alerts:";
    constexpr const char message_missing_incident_warning[] = "Warning: Missing/incorrect alert that generated incident in input JSON file.";
    constexpr const char message_missing_highest_score_path_entities[] = "Warning: Missing/incorrect entities for highest score path in input JSON file.";
    constexpr const char message_incident_not_found_error[] = "Warning: Alert that generated incident not found in alerts array.";

}

#endif //BITXDR_CONSTANTS_H
