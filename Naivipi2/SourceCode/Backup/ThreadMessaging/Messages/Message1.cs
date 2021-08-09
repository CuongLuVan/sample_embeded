using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ThreadMessaging.Messages
{
    /// <summary>
    /// Example user defined message class for the loop test
    /// </summary>
    public class Message1 : BaseMessage
    {
        /// <summary>
        /// Each thread in the chain will sleep this long before passing the message on
        /// </summary>
        public readonly int DelayInMilliSeconds;

        /// <summary>
        /// Constructor
        /// </summary>
        public Message1(int delayInMilliSeconds)
            : base(MessageType.Message1)
        {
            DelayInMilliSeconds = delayInMilliSeconds;
        }
    }
}
