# 

[toc]

### 多个子问题

- leader选举。
- 日志同步。
- 安全性。
- 日志压缩。
- 成员变更等

### 三个角色

- **Leader**：所有请求的处理者，Leader副本接受client的更新请求，本地处理后再同步至多个其他副本；
- **Follower**：请求的被动更新者，从Leader接受更新请求，然后写入本地日志文件
- **Candidate**：如果Follower副本在一段时间内没有收到Leader副本的心跳，则判断Leader可能已经故障，此时启动选主过程，此时副本会变成Candidate状态，直到选主结束。

### 三个结果

- 自己被选成了主，收到了majority的投票后，切为leader状态，并定期给其他server发心跳消息，告诉对方自己是current_term_id所标识的term的leader。每个term最多只有一个leader,term id作为logical clock，在每个RPC消息中都会带上，用于检测过期的消息。当一个server收到的RPC消息中的rpc_term_id比本地的的current_term_id更大时，就更新current_term_id为rpc_term_id，并且如果当前state为leader或candidate时，将自己的状态切换为follower。如果rpc_term_id比本地的current_term_id更小，则拒绝这个RPC消息。
- 别人成为了主。如1所述，当Candidator在等待投票的过程中，收到了大于或者等于本地的current_term_id的声明对方是leader的AppendEntriesRPC时，则将自己的state切成follower，并且更新本地的current_term_id。
- 没有选出主。当投票被瓜分，没有任何一个candidate收到了majority的vote时，没有leader被选出。这种情况下，每个candidate等待的投票的过程就超时了，接着candidates都会将本地的current_term_id再加1，发起RequestVoteRPC进行新一轮的leader election。

### 投票策略

- 每个节点只会给每个term投一票，具体的是否同意和后续的Safety有关。
- 当投票被瓜分后，所有的candidate同时超时，然后有可能进入新一轮的票数被瓜分，为了避免这个问题，Raft采用一种很简单的方法：每个Candidate的election timeout从150ms-300ms之间随机取，那么第一个超时的Candidate就可以发起新一轮的leader election，带着最大的term_id给其它所有server发送RequestVoteRPC消息，从而自己成为leader，然后给他们发送心跳消息以告诉他们自己是主。