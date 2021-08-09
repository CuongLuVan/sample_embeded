namespace Example
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.txtLoopTestDone = new System.Windows.Forms.TextBox();
            this.txtDelay = new System.Windows.Forms.TextBox();
            this.btnStartSleepLoop = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.listBox3 = new System.Windows.Forms.ListBox();
            this.listBox2 = new System.Windows.Forms.ListBox();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.txtLoadStatus = new System.Windows.Forms.TextBox();
            this.txtNumberOfMessages = new System.Windows.Forms.TextBox();
            this.btnStart = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txtLoopTestDone);
            this.groupBox1.Controls.Add(this.txtDelay);
            this.groupBox1.Controls.Add(this.btnStartSleepLoop);
            this.groupBox1.Location = new System.Drawing.Point(13, 13);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(217, 143);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Send a sleep message around the loop";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Delay in Seconds";
            // 
            // txtLoopTestDone
            // 
            this.txtLoopTestDone.Location = new System.Drawing.Point(50, 100);
            this.txtLoopTestDone.Name = "txtLoopTestDone";
            this.txtLoopTestDone.Size = new System.Drawing.Size(120, 20);
            this.txtLoopTestDone.TabIndex = 2;
            // 
            // txtDelay
            // 
            this.txtDelay.Location = new System.Drawing.Point(115, 19);
            this.txtDelay.Name = "txtDelay";
            this.txtDelay.Size = new System.Drawing.Size(67, 20);
            this.txtDelay.TabIndex = 1;
            this.txtDelay.Text = "1";
            // 
            // btnStartSleepLoop
            // 
            this.btnStartSleepLoop.Location = new System.Drawing.Point(50, 56);
            this.btnStartSleepLoop.Name = "btnStartSleepLoop";
            this.btnStartSleepLoop.Size = new System.Drawing.Size(120, 23);
            this.btnStartSleepLoop.TabIndex = 0;
            this.btnStartSleepLoop.Text = "Start";
            this.btnStartSleepLoop.UseVisualStyleBackColor = true;
            this.btnStartSleepLoop.Click += new System.EventHandler(this.btnStartSleepLoop_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.listBox3);
            this.groupBox2.Controls.Add(this.listBox2);
            this.groupBox2.Controls.Add(this.listBox1);
            this.groupBox2.Controls.Add(this.txtLoadStatus);
            this.groupBox2.Controls.Add(this.txtNumberOfMessages);
            this.groupBox2.Controls.Add(this.btnStart);
            this.groupBox2.Location = new System.Drawing.Point(236, 13);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(542, 545);
            this.groupBox2.TabIndex = 1;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Load and Dropped Message Test";
            // 
            // listBox3
            // 
            this.listBox3.FormattingEnabled = true;
            this.listBox3.Location = new System.Drawing.Point(317, 170);
            this.listBox3.Name = "listBox3";
            this.listBox3.Size = new System.Drawing.Size(120, 355);
            this.listBox3.TabIndex = 6;
            // 
            // listBox2
            // 
            this.listBox2.FormattingEnabled = true;
            this.listBox2.Location = new System.Drawing.Point(175, 170);
            this.listBox2.Name = "listBox2";
            this.listBox2.Size = new System.Drawing.Size(120, 355);
            this.listBox2.TabIndex = 5;
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(35, 170);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(120, 355);
            this.listBox1.TabIndex = 4;
            // 
            // txtLoadStatus
            // 
            this.txtLoadStatus.Location = new System.Drawing.Point(35, 115);
            this.txtLoadStatus.Name = "txtLoadStatus";
            this.txtLoadStatus.Size = new System.Drawing.Size(402, 20);
            this.txtLoadStatus.TabIndex = 2;
            // 
            // txtNumberOfMessages
            // 
            this.txtNumberOfMessages.Location = new System.Drawing.Point(236, 26);
            this.txtNumberOfMessages.Name = "txtNumberOfMessages";
            this.txtNumberOfMessages.Size = new System.Drawing.Size(100, 20);
            this.txtNumberOfMessages.TabIndex = 1;
            this.txtNumberOfMessages.Text = "10";
            // 
            // btnStart
            // 
            this.btnStart.Location = new System.Drawing.Point(185, 71);
            this.btnStart.Name = "btnStart";
            this.btnStart.Size = new System.Drawing.Size(100, 23);
            this.btnStart.TabIndex = 0;
            this.btnStart.Text = "Start";
            this.btnStart.UseVisualStyleBackColor = true;
            this.btnStart.Click += new System.EventHandler(this.btnStart_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(32, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(189, 13);
            this.label2.TabIndex = 7;
            this.label2.Text = "# of messages for each thread to send";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(846, 584);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "Form1";
            this.Text = "Thread Messaging Demo";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txtLoopTestDone;
        private System.Windows.Forms.TextBox txtDelay;
        private System.Windows.Forms.Button btnStartSleepLoop;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtLoadStatus;
        private System.Windows.Forms.TextBox txtNumberOfMessages;
        private System.Windows.Forms.Button btnStart;
        private System.Windows.Forms.ListBox listBox3;
        private System.Windows.Forms.ListBox listBox2;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label label2;

    }
}

