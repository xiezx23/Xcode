# Generated by the gRPC Python protocol compiler plugin. DO NOT EDIT!
"""Client and server classes corresponding to protobuf-defined services."""
import grpc

import managementServer_pb2 as managementServer__pb2


class managementServerStub(object):
    """Missing associated documentation comment in .proto file."""

    def __init__(self, channel):
        """Constructor.

        Args:
            channel: A grpc.Channel.
        """
        self.serverOnline = channel.unary_unary(
                '/managementServer/serverOnline',
                request_serializer=managementServer__pb2.serverInfo.SerializeToString,
                response_deserializer=managementServer__pb2.ma_reply.FromString,
                )
        self.serverOffline = channel.unary_unary(
                '/managementServer/serverOffline',
                request_serializer=managementServer__pb2.serverId.SerializeToString,
                response_deserializer=managementServer__pb2.ma_reply.FromString,
                )
        self.getServerList = channel.unary_unary(
                '/managementServer/getServerList',
                request_serializer=managementServer__pb2.empty.SerializeToString,
                response_deserializer=managementServer__pb2.serverList.FromString,
                )
        self.lockFile = channel.unary_unary(
                '/managementServer/lockFile',
                request_serializer=managementServer__pb2.lockInfo.SerializeToString,
                response_deserializer=managementServer__pb2.lockReply.FromString,
                )
        self.unlockFile = channel.unary_unary(
                '/managementServer/unlockFile',
                request_serializer=managementServer__pb2.lockInfo.SerializeToString,
                response_deserializer=managementServer__pb2.lockReply.FromString,
                )


class managementServerServicer(object):
    """Missing associated documentation comment in .proto file."""

    def serverOnline(self, request, context):
        """数据服务器上线后向管理服务器登记注册
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def serverOffline(self, request, context):
        """数据服务器下线后向管理服务器登记注销
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def getServerList(self, request, context):
        """获取当前在线数据服务器信息
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def lockFile(self, request, context):
        """给文件上锁
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')

    def unlockFile(self, request, context):
        """给文件解锁
        """
        context.set_code(grpc.StatusCode.UNIMPLEMENTED)
        context.set_details('Method not implemented!')
        raise NotImplementedError('Method not implemented!')


def add_managementServerServicer_to_server(servicer, server):
    rpc_method_handlers = {
            'serverOnline': grpc.unary_unary_rpc_method_handler(
                    servicer.serverOnline,
                    request_deserializer=managementServer__pb2.serverInfo.FromString,
                    response_serializer=managementServer__pb2.ma_reply.SerializeToString,
            ),
            'serverOffline': grpc.unary_unary_rpc_method_handler(
                    servicer.serverOffline,
                    request_deserializer=managementServer__pb2.serverId.FromString,
                    response_serializer=managementServer__pb2.ma_reply.SerializeToString,
            ),
            'getServerList': grpc.unary_unary_rpc_method_handler(
                    servicer.getServerList,
                    request_deserializer=managementServer__pb2.empty.FromString,
                    response_serializer=managementServer__pb2.serverList.SerializeToString,
            ),
            'lockFile': grpc.unary_unary_rpc_method_handler(
                    servicer.lockFile,
                    request_deserializer=managementServer__pb2.lockInfo.FromString,
                    response_serializer=managementServer__pb2.lockReply.SerializeToString,
            ),
            'unlockFile': grpc.unary_unary_rpc_method_handler(
                    servicer.unlockFile,
                    request_deserializer=managementServer__pb2.lockInfo.FromString,
                    response_serializer=managementServer__pb2.lockReply.SerializeToString,
            ),
    }
    generic_handler = grpc.method_handlers_generic_handler(
            'managementServer', rpc_method_handlers)
    server.add_generic_rpc_handlers((generic_handler,))


 # This class is part of an EXPERIMENTAL API.
class managementServer(object):
    """Missing associated documentation comment in .proto file."""

    @staticmethod
    def serverOnline(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/managementServer/serverOnline',
            managementServer__pb2.serverInfo.SerializeToString,
            managementServer__pb2.ma_reply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def serverOffline(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/managementServer/serverOffline',
            managementServer__pb2.serverId.SerializeToString,
            managementServer__pb2.ma_reply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def getServerList(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/managementServer/getServerList',
            managementServer__pb2.empty.SerializeToString,
            managementServer__pb2.serverList.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def lockFile(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/managementServer/lockFile',
            managementServer__pb2.lockInfo.SerializeToString,
            managementServer__pb2.lockReply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)

    @staticmethod
    def unlockFile(request,
            target,
            options=(),
            channel_credentials=None,
            call_credentials=None,
            insecure=False,
            compression=None,
            wait_for_ready=None,
            timeout=None,
            metadata=None):
        return grpc.experimental.unary_unary(request, target, '/managementServer/unlockFile',
            managementServer__pb2.lockInfo.SerializeToString,
            managementServer__pb2.lockReply.FromString,
            options, channel_credentials,
            insecure, call_credentials, compression, wait_for_ready, timeout, metadata)