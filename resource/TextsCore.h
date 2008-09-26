#ifndef TextsCoreH
#define TextsCoreH

#define UNKNOWN_KEY2    1
#define DIFFERENT_KEY3  2
#define OLD_KEY         3

#define SCRIPT_HELP_HELP        4
#define SCRIPT_EXIT_HELP        5
#define SCRIPT_OPEN_HELP2       6
#define SCRIPT_CLOSE_HELP       7
#define SCRIPT_SESSION_HELP     8
#define SCRIPT_PWD_HELP         9
#define SCRIPT_CD_HELP          10
#define SCRIPT_LS_HELP          11
#define SCRIPT_LPWD_HELP        12
#define SCRIPT_LCD_HELP         13
#define SCRIPT_LLS_HELP         14
#define SCRIPT_RM_HELP          15
#define SCRIPT_RMDIR_HELP       16
#define SCRIPT_MV_HELP          17
#define SCRIPT_CHMOD_HELP       18
#define SCRIPT_LN_HELP          19
#define SCRIPT_MKDIR_HELP       20
#define SCRIPT_GET_HELP2        21
#define SCRIPT_PUT_HELP2        22
#define SCRIPT_OPTION_HELP5     23
#define SCRIPT_SYNCHRONIZE_HELP2 24
#define SCRIPT_KEEPUPTODATE_HELP2 25
#define SCRIPT_CALL_HELP2       26

#define CORE_ERROR_STRINGS      100
#define KEY_NOT_VERIFIED        101
#define CONNECTION_FAILED       102
#define USER_TERMINATED         103
#define LOST_CONNECTION         104
#define CANT_DETECT_RETURN_CODE 105
#define COMMAND_FAILED          106
#define COMMAND_FAILED_CODEONLY 107
#define INVALID_OUTPUT_ERROR    108
#define READ_CURRENT_DIR_ERROR  109
#define SKIP_STARTUP_MESSAGE_ERROR 110
#define CHANGE_DIR_ERROR        111
#define LIST_DIR_ERROR          113
#define LIST_LINE_ERROR         114
#define RIGHTS_ERROR            115
#define CLEANUP_CONFIG_ERROR    116
#define CLEANUP_HOSTKEYS_ERROR  117
#define CLEANUP_SEEDFILE_ERROR  118
#define CLEANUP_SESSIONS_ERROR  119
#define DETECT_RETURNVAR_ERROR  120
#define LOOKUP_GROUPS_ERROR     121
#define FILE_NOT_EXISTS         122
#define CANT_GET_ATTRS          123
#define OPENFILE_ERROR          124
#define READ_ERROR              125
#define COPY_FATAL              126
#define TOREMOTE_COPY_ERROR     127
#define TOLOCAL_COPY_ERROR      128
#define SCP_EMPTY_LINE          129
#define SCP_ILLEGAL_TIME_FORMAT 130
#define SCP_INVALID_CONTROL_RECORD 131
#define COPY_ERROR              132
#define SCP_ILLEGAL_FILE_DESCRIPTOR 133
#define NOT_DIRECTORY_ERROR     134
#define CREATE_DIR_ERROR        135
#define CREATE_FILE_ERROR       136
#define WRITE_ERROR             137
#define CANT_SET_ATTRS          138
#define REMOTE_ERROR            139
#define DELETE_FILE_ERROR       140
#define LOG_GEN_ERROR           141
#define LOG_OPENERROR           142
#define RENAME_FILE_ERROR       143
#define RENAME_CREATE_FILE_EXISTS 144
#define RENAME_CREATE_DIR_EXISTS 145
#define CHANGE_HOMEDIR_ERROR    146
#define UNALIAS_ALL_ERROR       147
#define UNSET_NATIONAL_ERROR    149
#define FIRST_LINE_EXPECTED     150
#define CLEANUP_INIFILE_ERROR   151
#define ATTEMPT_TO_WRITE_TO_PARENT_DIR  152
#define AUTHENTICATION_LOG      153
#define AUTHENTICATION_FAILED   154
#define NOT_CONNECTED           155
#define SAVE_KEY_ERROR          156
#define SSH_EXITCODE            158
#define SFTP_INVALID_TYPE       159
#define SFTP_VERSION_NOT_SUPPORTED 160
#define SFTP_MESSAGE_NUMBER     161
#define SFTP_STATUS_OK          162
#define SFTP_STATUS_EOF         163
#define SFTP_STATUS_NO_SUCH_FILE 164
#define SFTP_STATUS_PERMISSION_DENIED 165
#define SFTP_STATUS_FAILURE     166
#define SFTP_STATUS_BAD_MESSAGE 167
#define SFTP_STATUS_NO_CONNECTION 168
#define SFTP_STATUS_CONNECTION_LOST 169
#define SFTP_STATUS_OP_UNSUPPORTED 170
#define SFTP_ERROR_FORMAT2      171
#define SFTP_STATUS_UNKNOWN     172
#define READ_SYMLINK_ERROR      173
#define EMPTY_DIRECTORY         174
#define SFTP_NON_ONE_FXP_NAME_PACKET 175
#define SFTP_REALPATH_ERROR     176
#define CHANGE_PROPERTIES_ERROR 177
#define SFTP_INITIALIZE_ERROR   178
#define TIMEZONE_ERROR          179
#define SFTP_CREATE_FILE_ERROR  180
#define SFTP_OPEN_FILE_ERROR    181
#define SFTP_CLOSE_FILE_ERROR   182
#define NOT_FILE_ERROR          183
#define RENAME_AFTER_RESUME_ERROR 184
#define CREATE_LINK_ERROR       185
#define INVALID_SHELL_COMMAND   186
#define SFTP_SERVER_MESSAGE_UNSUPPORTED 187
#define INVALID_OCTAL_PERMISSIONS 188
#define SFTP_INVALID_EOL        189
#define SFTP_UNKNOWN_FILE_TYPE  190
#define SFTP_STATUS_INVALID_HANDLE 191
#define SFTP_STATUS_NO_SUCH_PATH 192
#define SFTP_STATUS_FILE_ALREADY_EXISTS 193
#define SFTP_STATUS_WRITE_PROTECT 194
#define SFTP_STATUS_NO_MEDIA    195
#define DECODE_UTF_ERROR        196
#define CUSTOM_COMMAND_ERROR    197
#define LOCALE_LOAD_ERROR       198
#define SFTP_INCOMPLETE_BEFORE_EOF 199
#define CALCULATE_SIZE_ERROR    200
#define SFTP_PACKET_TOO_BIG     201
#define SCP_INIT_ERROR          202
#define DUPLICATE_BOOKMARK      203
#define MOVE_FILE_ERROR         204
#define SFTP_PACKET_TOO_BIG_INIT_EXPLAIN 205
#define PRESERVE_TIME_PERM_ERROR 206
#define ACCESS_VIOLATION_ERROR  207
#define SFTP_STATUS_NO_SPACE_ON_FILESYSTEM 208
#define SFTP_STATUS_QUOTA_EXCEEDED 209
#define SFTP_STATUS_UNKNOWN_PRINCIPAL 210
#define COPY_FILE_ERROR         211
#define CUSTOM_COMMAND_UNTERMINATED 212
#define CUSTOM_COMMAND_UNKNOWN  213
#define CUSTOM_COMMAND_FILELIST_ERROR 214
#define SCRIPT_COMMAND_UNKNOWN  215
#define SCRIPT_COMMAND_AMBIGUOUS 216
#define SCRIPT_MISSING_PARAMS   217
#define SCRIPT_TOO_MANY_PARAMS  218
#define SESSION_NOT_EXISTS_ERROR 219
#define SCRIPT_NO_SESSION       223
#define SCRIPT_SESSION_INDEX_INVALID 224
#define SCRIPT_OPTION_UNKNOWN   225
#define SCRIPT_VALUE_UNKNOWN    226
#define UNKNOWN_SOCKET_STATUS   227
#define DELETE_ON_RESUME_ERROR  228
#define SFTP_PACKET_ERROR       229
#define ITEM_NAME_INVALID       230
#define SFTP_STATUS_LOCK_CONFLICT 231
#define SFTP_STATUS_DIR_NOT_EMPTY 232
#define SFTP_STATUS_NOT_A_DIRECTORY 233
#define SFTP_STATUS_INVALID_FILENAME 234
#define SFTP_STATUS_LINK_LOOP   235
#define SFTP_STATUS_CANNOT_DELETE 236
#define SFTP_STATUS_INVALID_PARAMETER 237
#define SFTP_STATUS_FILE_IS_A_DIRECTORY 238
#define SFTP_STATUS_BYTE_RANGE_LOCK_CONFLICT 239
#define SFTP_STATUS_BYTE_RANGE_LOCK_REFUSED 240
#define SFTP_STATUS_DELETE_PENDING 241
#define SFTP_STATUS_FILE_CORRUPT 242
#define KEY_TYPE_UNKNOWN        243
#define KEY_TYPE_UNSUPPORTED    244
#define KEY_TYPE_DIFFERENT_SSH  245
#define SFTP_OVERWRITE_FILE_ERROR 246
#define SFTP_OVERWRITE_DELETE_BUTTON 247
#define SPACE_AVAILABLE_ERROR   248
#define TUNNEL_NO_FREE_PORT     249
#define EVENT_SELECT_ERROR      250
#define UNEXPECTED_CLOSE_ERROR  251
#define TUNNEL_ERROR            252
#define CHECKSUM_ERROR          253
#define INTERNAL_ERROR          254
#define FZ_NOTSUPPORTED         255
#define FTP_ACCESS_DENIED       256
#define FTP_CREDENTIAL_PROMPT   257
#define FTP_PWD_RESPONSE_ERROR  258
#define FTP_UNSUPPORTED         259
#define SCRIPT_UNKNOWN_SWITCH   260
#define TRANSFER_ERROR          261
#define EXECUTE_APP_ERROR       262
#define FILE_NOT_FOUND          263
#define DOCUMENT_WAIT_ERROR     264
#define SPEED_INVALID           265

#define CORE_CONFIRMATION_STRINGS 300
#define CONFIRM_PROLONG_TIMEOUT2 301
#define PROMPT_KEY_PASSPHRASE   303
#define FILE_OVERWRITE          304
#define DIRECTORY_OVERWRITE     305
#define CIPHER_BELOW_TRESHOLD   306
#define CIPHER_TYPE_BOTH        307
#define CIPHER_TYPE_CS          308
#define CIPHER_TYPE_SC          309
#define RESUME_TRANSFER         310
#define PARTIAL_BIGGER_THAN_SOURCE 311
#define APPEND_OR_RESUME        312
#define FILE_OVERWRITE_DETAILS  313
#define READ_ONLY_OVERWRITE     314
#define LOCAL_FILE_OVERWRITE    315
#define REMOTE_FILE_OVERWRITE   316
#define TIMEOUT_STILL_WAITING   321
#define KEX_BELOW_TRESHOLD      322
#define RECONNECT_BUTTON        323
#define RENAME_BUTTON           324
#define TUNNEL_SESSION_NAME     327
#define PASSWORD_TITLE          328
#define PASSPHRASE_TITLE        329
#define SERVER_PROMPT_TITLE     330
#define USERNAME_TITLE          331
#define USERNAME_PROMPT2        332
#define SERVER_PROMPT_TITLE2    333
#define NEW_PASSWORD_TITLE      334
#define PROMPT_PROMPT           335
#define TIS_INSTRUCTION         336
#define CRYPTOCARD_INSTRUCTION  337
#define PASSWORD_PROMPT         338
#define KEYBINTER_INSTRUCTION   339
#define NEW_PASSWORD_CURRENT_PROMPT 340
#define NEW_PASSWORD_NEW_PROMPT 341
#define NEW_PASSWORD_CONFIRM_PROMPT 342
#define TUNNEL_INSTRUCTION      343
#define RENAME_TITLE            344
#define RENAME_PROMPT2          345

#define CORE_INFORMATION_STRINGS 400
#define YES_STR                 401
#define NO_STR                  402
#define SESSION_INFO_TIP        403
#define VERSION                 404
#define CLOSED_ON_COMPLETION    405
#define SFTP_PROTOCOL_NAME2     406
#define FS_RENAME_NOT_SUPPORTED 407
#define SFTP_NO_EXTENSION_INFO  408
#define SFTP_EXTENSION_INFO     409
#define APPEND_BUTTON           412
#define YES_TO_NEWER_BUTTON     413
#define SCRIPT_HELP_DESC        414
#define SCRIPT_EXIT_DESC        415
#define SCRIPT_OPEN_DESC        416
#define SCRIPT_CLOSE_DESC       417
#define SCRIPT_SESSION_DESC     418
#define SCRIPT_PWD_DESC         419
#define SCRIPT_CD_DESC          420
#define SCRIPT_LS_DESC          421
#define SCRIPT_LPWD_DESC        422
#define SCRIPT_LCD_DESC         423
#define SCRIPT_LLS_DESC         424
#define SCRIPT_RM_DESC          425
#define SCRIPT_RMDIR_DESC       426
#define SCRIPT_MV_DESC          427
#define SCRIPT_CHMOD_DESC       428
#define SCRIPT_LN_DESC          429
#define SCRIPT_MKDIR_DESC       430
#define SCRIPT_GET_DESC         431
#define SCRIPT_PUT_DESC         432
#define SCRIPT_OPTION_DESC      433
#define SCRIPT_SYNCHRONIZE_DESC 434
#define SCRIPT_KEEPUPTODATE_DESC 435
#define SCRIPT_HOST_PROMPT      436
#define SCRIPT_ACTIVE_SESSION   438
#define SCRIPT_SESSION_CLOSED   439
#define SCRIPT_SYNCHRONIZE      440
#define SCRIPT_SYNCHRONIZE_DELETED 441
#define SCRIPT_KEEPING_UP_TO_DATE 442
#define SKIP_ALL_BUTTON         443
#define SCRIPT_CALL_DESC2       444
#define COPY_PARAM_PRESET_ASCII 445
#define COPY_PARAM_PRESET_BINARY 446
#define COPY_PARAM_PRESET_EXCLUDE 447
#define COPY_INFO_TRANSFER_TYPE 448
#define COPY_INFO_FILENAME      449
#define COPY_INFO_PERMISSIONS   450
#define COPY_INFO_ADD_X_TO_DIRS 451
#define COPY_INFO_TIMESTAMP     452
#define COPY_INFO_EXCLUDE_MASK  453
#define COPY_INFO_INCLUDE_MASK  454
#define COPY_INFO_CLEAR_ARCHIVE 455
#define COPY_INFO_DONT_REPLACE_INV_CHARS 456
#define COPY_INFO_DONT_PRESERVE_TIME 458
#define COPY_INFO_DONT_CALCULATE_SIZE 459
#define COPY_INFO_DEFAULT       460
#define COPY_RULE_HOSTNAME      461
#define COPY_RULE_USERNAME      462
#define COPY_RULE_REMOTE_DIR    463
#define COPY_RULE_LOCAL_DIR     464
#define SYNCHRONIZE_SCAN        465
#define SYNCHRONIZE_START       466
#define SYNCHRONIZE_CHANGE      467
#define SYNCHRONIZE_UPLOADED    468
#define SYNCHRONIZE_DELETED     469
#define COPY_INFO_NOT_USABLE    470
#define COPY_INFO_IGNORE_PERM_ERRORS 472
#define AUTH_TRANSL_USERNAME    473
#define AUTH_TRANSL_KEYB_INTER  474
#define AUTH_TRANSL_PUBLIC_KEY  475
#define AUTH_TRANSL_WRONG_PASSPHRASE 476
#define AUTH_TRANSL_ACCESS_DENIED 477
#define AUTH_TRANSL_PUBLIC_KEY_AGENT 478
#define AUTH_TRANSL_TRY_PUBLIC_KEY 479
#define AUTH_PASSWORD           480
#define OPEN_TUNNEL             481
#define STATUS_CLOSED           482
#define STATUS_LOOKUPHOST       484
#define STATUS_CONNECT          485
#define STATUS_AUTHENTICATE     486
#define STATUS_AUTHENTICATED    487
#define STATUS_STARTUP          488
#define STATUS_OPEN_DIRECTORY   489
#define STATUS_READY            490
#define USING_TUNNEL            491
#define AUTH_TRANSL_KEY_REFUSED 492
#define PFWD_TRANSL_ADMIN       493
#define PFWD_TRANSL_CONNECT     494
#define NET_TRANSL_REFUSED      495
#define NET_TRANSL_RESET        496
#define NET_TRANSL_TIMEOUT      497
#define SESSION_INFO_TIP_NO_SSH 498
#define RESUME_BUTTON           499
#define FTP_NO_FEATURE_INFO     500
#define FTP_FEATURE_INFO        501
#define COPY_INFO_CPS_LIMIT     502
#define COPY_KEY_BUTTON         503
#define UPDATE_KEY_BUTTON       504
#define ADD_KEY_BUTTON          505
#define COPY_INFO_PRESERVE_READONLY 506
#define SCRIPT_SYNCHRONIZE_COLLECTING 507
#define SCRIPT_SYNCHRONIZE_SYNCHRONIZING 508
#define SCRIPT_SYNCHRONIZE_NODIFFERENCE 509
#define SPEED_UNLIMITED         510

#define CORE_VARIABLE_STRINGS   600
#define PUTTY_BASED_ON          601
#define PUTTY_VERSION           602
#define PUTTY_COPYRIGHT         603
#define PUTTY_URL               604
#define FILEZILLA_BASED_ON      605
#define FILEZILLA_VERSION       606
#define FILEZILLA_COPYRIGHT     607
#define FILEZILLA_URL           608

#endif // TextsCore
