using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ThreadMessaging.Messages
{
    /// <summary>
    /// The different messages the managed threads send to each other.
    /// Add your own definitions here as needed.
    /// </summary>
    public enum MessageType
    {
        StopThread,     // Default one to have each thread exit its main processing loop

        // Add your message definitions here
        Message1,
        Message2A,
        Message2B
    }

    /// <summary>
    /// Base for all specific messages
    /// </summary>
    public abstract partial class BaseMessage
    {
        /// <summary>
        /// The specific message being instantiated
        /// </summary>
        public readonly MessageType MsgType;

        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="msgType"></param>
        public BaseMessage(MessageType msgType)
        {
            this.MsgType = msgType;
        }
    }
}
