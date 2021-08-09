using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ThreadMessaging.Messages
{
    /// <summary>
    /// This message signals the worker thread to go into a loop sending out Message2Bs
    /// </summary>
    public class Message2A : BaseMessage
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public Message2A()
            : base(MessageType.Message2A)
        {
        }
    }
}
