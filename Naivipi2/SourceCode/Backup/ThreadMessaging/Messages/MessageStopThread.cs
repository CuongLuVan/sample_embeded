using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ThreadMessaging.Messages
{
    /// <summary>
    /// Default message to signal a managed thread to exit its main processing loop
    /// </summary>
    internal class MessageStopThread : BaseMessage
    {
        /// <summary>
        /// Constructor
        /// </summary>
        public MessageStopThread()
            : base(MessageType.StopThread)
        {
        }
    }
}
