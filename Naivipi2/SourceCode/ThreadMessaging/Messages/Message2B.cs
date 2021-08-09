using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ThreadMessaging.Messages
{
    /// <summary>
    /// This message signals the worker thread to go into a loop sending out Message2Bs
    /// </summary>
    public class Message2B : BaseMessage
    {
        /// <summary>
        /// The current sequence number
        /// </summary>
        public readonly int SequenceNumber;

        /// <summary>
        /// The name of the managed thread sending this message
        /// </summary>
        public readonly string ThreadName;

        /// <summary>
        /// Constructor
        /// </summary>
        public Message2B(int sequenceNumber, string threadName)
            : base(MessageType.Message2B)
        {
            SequenceNumber = sequenceNumber;
            ThreadName = threadName;
        }
    }
}
