/****************************
 * Base class for AODV Messages 
 * **************************/
class AODVMessage
{
  public:
    // Common AODV message header properties
    int type; // 1 - request, 2 - response, 3 - error
    bool reserved;
    unsigned long destination_ip;
    int destination_sequence_num;

    // Virtual serialization functions
    virtual char* serialize() = 0;
    virtual void deserialize(char* ser_data) = 0;
};

/****************************
 * AODV message sent to request a path 
 * **************************/
class AODVRequest: public AODVMessage
{
  public:
    // Message header properties
    bool join_flag;
    bool repair_flag;
    bool gratuitous_flag;
    bool destination_only_flag;
    bool unknown_sequence_number;
    int hop_count;
    int rreq_id;
    unsigned long originator_ip;
    int originator_sequence_number;
    
    // Constructors
    AODVRequest(); // Default used when deserializing
    AODVRequest(unsigned long orig_ip, unsigned long dest_ip);

    // Serialization functions
    char* serialize();
    void deserialize(char* ser_data);
};

/****************************
 * AODV message sent in response to a request if:
 *      1 - current node is the destination
 *      2 - current node has an active route to destination
 * **************************/
class AODVResponse: public AODVMessage
{
  public:
    // Message header properties
    bool repair_flag;
    bool ack_required;
    int prefix_size; // Next hop can be any node with same prefix as dest
    int hop_count;
    unsigned long originator_ip;
    int lifetime; // In Milliseconds

    // Constructors
    AODVResponse(); // Default used when deserializing
    AODVResponse(unsigned long orig_ip, unsigned long dest_ip);

    // Serialization functions
    char* serialize();
    void deserialize(char* ser_data);
};

/****************************
 * AODV message sent due to error in transmission 
 * **************************/
class AODVError: public AODVMessage
{
    bool no_delete_flag;
    int dest_count; // Number of unreacheable destinations
};
